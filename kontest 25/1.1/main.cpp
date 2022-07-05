#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>


#include <iomanip>
#include <random>
#include <ctime>
#include <string>
#include <functional>


using namespace std;


using cpx = complex<double>;
const long double PI = std::acos(-1.0L);
long long prime;

struct UInt {
    static const long long BASE = (long long)1e9; // Основание системы счисления
    static const long long WIDTH = 9;       // Количество десятичных цифр, которые хранятся в одной цифре

    // Вектор под цифры числа:
    std::vector<long long> digits;

    // Конструкторы
    UInt(int64_t number = 0);
    UInt(const std::string& s);
    UInt(const std::vector<long long>& digits);

    // Методы нормализации и сравнения:
    UInt& normalize(); // удаление лидирующих нулей и проверка на принадлежность цифр диапазону [0, BASE)
    long long compare(const UInt& other) const; // Сравнение (меньше = -1, равно = 0, больше = 1)

    // Методы умножения:
    UInt slow_mult(const UInt& other) const; // Медленное произведение (работает довольно быстро на числах небольшой длины)
    UInt fast_mult(const UInt& other) const; // Быстрое произведение (на основе Быстрого Преобразования Фурье комплексные числа)
    UInt mult(const UInt& other) const; // Комбинированный метод умножения на основе экспериментальных данных

    // Метод деления:
    std::pair<UInt, UInt> div_mod(const UInt& other) const; // Целая часть и остаток от деления

    // Операторы:
    UInt& operator+=(const long long num);     // Прибавление короткого
    UInt& operator+=(const UInt& other); // Прибавление длинного
    UInt& operator-=(const long long num);     // Вычитание короткого
    UInt& operator-=(const UInt& other); // Вычитание длинного
    UInt& operator*=(const long long num);     // Умножение на короткое
    UInt& operator*=(const UInt& other); // Умножение на длинное
    UInt& operator/=(const long long num);     // Деление на короткое
    UInt& operator/=(const UInt& other); // Деление на длинное
    UInt& operator%=(const UInt& other); // Остаток от деления на длинное
};

std::istream& operator>>(std::istream&, UInt&); // Ввод из потока
std::ostream& operator<<(std::ostream&, const UInt&); // Вывод в поток

UInt pow(UInt, long long); // Возведение в степень
UInt gcd(UInt, UInt); // Наибольший общий делитель

UInt operator+(const UInt&, const UInt&);
UInt operator-(const UInt&, const UInt&);
UInt operator*(const UInt&, const UInt&);
UInt operator/(const UInt&, const UInt&);
UInt operator%(const UInt&, const UInt&);

UInt operator+(const UInt&, const long long);
UInt operator+(const long long, const UInt&);
UInt operator-(const UInt&, const long long);
UInt operator*(const UInt&, const long long);
UInt operator*(const long long, const UInt&);
UInt operator/(const UInt&, const long long);
UInt operator^(const UInt&, const long long); // возведение в степень

bool operator<(const UInt&, const UInt&);
bool operator>(const UInt&, const UInt&);
bool operator<=(const UInt&, const UInt&);
bool operator>=(const UInt&, const UInt&);
bool operator==(const UInt&, const UInt&);
bool operator!=(const UInt&, const UInt&);

UInt& UInt::normalize() {
    while (digits.back() == 0 && (long long)digits.size() > 1) digits.pop_back();
    for (auto d : digits) assert(0 <= d && d < BASE);
    return *this;
}

// Конструктор от короткого целого
UInt::UInt(int64_t number) {
    assert(number >= 0);
    do {
        digits.push_back(number % BASE);
        number /= BASE;
    } while (number > 0);
    normalize();
}

// Конструктор от вектора из цифр:
UInt::UInt(const std::vector<long long>& digits) : digits(digits) {
    normalize();
}

// Конструктор от строчки:
UInt::UInt(const std::string& s) {
    const long long size = (long long)s.size();
    for (long long idGroup = 1, nGroups = size / WIDTH; idGroup <= nGroups; ++idGroup) {
        digits.push_back(std::stoi(s.substr(size-idGroup * WIDTH, WIDTH)));
    }
    if (size % WIDTH != 0) {
        digits.push_back(std::stoi(s.substr(0, size % WIDTH)));
    }
    normalize();
}



// Прибавление короткого:
UInt& UInt::operator+=(const long long num) {
    assert(num >= 0);
    if (num >= BASE) {
        return *this += UInt(num);
    }
    long long rem = num;
    for (long long i = 0; rem > 0; ++i) {
        if (i >= (long long)digits.size()) digits.push_back(0);
        rem += digits[i];
        if (rem >= BASE) {
            digits[i] = rem - BASE;
            rem = 1;
        } else {
            digits[i] = rem;
            rem = 0;
        }
    }
    return this->normalize();
}

// Прибавление длинного:
UInt& UInt::operator+=(const UInt& other) {
    if (other.digits.size() == 1u) {
        return *this += other.digits[0];
    }
    const long long s1 = this->digits.size();
    const long long s2 = other.digits.size();
    long long rem = 0;
    for (long long i = 0; i < s1 || i < s2 || rem > 0; ++i) {
        long long d1 = i < s1 ? this->digits[i] : (digits.push_back(0), 0);
        long long d2 = i < s2 ? other.digits[i] : 0;
        rem += d1 + d2;
        auto div = rem / BASE;
        digits[i] = rem - div * BASE;
        rem = div;
    }
    return this->normalize();
}

// Вычитание короткого:
UInt& UInt::operator-=(const long long num) {
    assert(num >= 0);
    if (num >= BASE) {
        return *this -= UInt(num);
    }
    long long rem = -num;
    for (long long i = 0; i < (long long)digits.size() && rem < 0; ++i) {
        rem += digits[i];
        if (rem < 0) { // Занимаем разряд
            digits[i] = rem + BASE;
            rem = -1;
        } else {
            digits[i] = rem;
            rem = 0;
        }
    }
    assert(rem == 0);
    return this->normalize();
}

// Вычитание длинного:
UInt& UInt::operator-=(const UInt& other) {
    if (other.digits.size() == 1u) {
        return *this -= other.digits[0];
    }
    const long long s1 = this->digits.size();
    const long long s2 = other.digits.size();
    assert(s1 >= s2);
    long long rem = 0;
    for (long long i = 0; i < s1; ++i) {
        long long d2 = i < s2 ? other.digits[i] : 0;
        rem += this->digits[i] - d2;
        if (rem < 0) {
            digits[i] = rem + BASE;
            rem = -1;
        } else {
            digits[i] = rem;
            rem = 0;
            if (i >= s2) break;
        }
    }
    assert(rem == 0); // Иначе *this < other
    return this->normalize();
}

// Умножение на короткое:
UInt& UInt::operator*=(const long long num) {
    assert(num >= 0);
    if (num >= BASE) {
        return *this *= UInt(num);
    }
    int64_t rem = 0;
    for (auto& d : digits) {
        rem += 1LL * d * num;
        auto div = rem / BASE;
        d = rem - div * BASE;
        rem = div;
    }
    if (rem > 0) digits.push_back(rem);
    return this->normalize();
}

// Медленное произведение:
UInt UInt::slow_mult(const UInt& other) const {
    if (other.digits.size() == 1u) {
        return *this * other.digits[0];
    }
    const long long s1 = (long long)this->digits.size();
    const long long s2 = (long long)other.digits.size();
    std::vector<long long> temp(s1+s2);
    for (long long i = 0; i < s1; ++i) {
        int64_t rem = 0;
        for (long long j = 0; j < s2; ++j) {
            rem += temp[i+j] + 1LL * this->digits[i] * other.digits[j];
            auto div = rem / BASE;
            temp[i+j] = rem - div * BASE;
            rem = div;
        }
        if (rem > 0) temp[i+s2] += rem;
    }
    return UInt(temp);
}

// Быстрое умножение на основе быстрого преобразования Фурье:
UInt UInt::fast_mult(const UInt& other) const {
    if (other.digits.size() == 1u) {
        return *this * other.digits[0];
    }

    // Разворот битов в числе num:
    std::function<long long(long long, long long)> reverse = [](long long number, long long nBits) {
        long long res = 0;
        for (long long i = 0; i < nBits; ++i) {
            if (number & (1 << i)) {
                res |= 1 << (nBits-1-i);
            }
        }
        return res;
    };

    typedef std::complex<long double> complex;
    // Быстрое преобразование Фурье:
    std::function<void(std::vector<complex>&, bool)> fft = [&reverse](std::vector<complex> & a, bool invert) {
        const long long n = (long long)a.size();
        long long nBits = 0;
        while ((1 << nBits) < n) ++nBits;



        for (long long i = 0; i < n; ++i) {
            if (i < reverse(i, nBits)) {
                std::swap(a[i], a[reverse(i, nBits)]);
            }
        }

        for (long long len = 2; len <= n; len <<= 1) {
            auto ang = 2*PI / len * (invert ? -1 : 1);
            complex wlen (std::cos(ang), std::sin(ang));
            for (long long i = 0; i < n; i += len) {
                complex w(1);
                for (long long j = 0; j < len / 2; ++j) {
                    complex u = a[i+j];
                    complex v = a[i+j+len / 2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (long long i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    };

    // Подготавливаем вектора из комплексных коэффициентов fa и fb:
    // Так как происходит потеря точности из-за арифметики с плавающей точкой, основание системы необходимо понизить:
    assert(BASE == 1000 * 1000 * 1000);
    std::function<std::vector<complex>(const UInt&)> prepare = [](const UInt& number) {
        std::vector<complex> result;
        result.reserve(3 * number.digits.size());
        for (auto d : number.digits) {
            result.push_back(d % 1000);
            result.push_back(d / 1000 % 1000);
            result.push_back(d / 1000000);
        }
        return result;
    };

    auto fa = prepare(*this);
    auto fb = prepare(other);

    // Округляем размер векторов до ближайшей степени двойки:
    long long n = 1;
    while (n < (long long)std::max(fa.size(), fb.size())) n *= 2;
    n *= 2;
    fa.resize(n);
    fb.resize(n);

    // Вызываем прямое преобразование Фурье:
    fft (fa, false);
    fft (fb, false);
    // Перемножаем результаты:
    for (long long i = 0; i < n; ++i) {
        fa[i] *= fb[i];
    }
    // Вызываем обратное преобразование Фурье:
    fft (fa, true);
    // Копируем ответ с округлениями:
    std::vector<int64_t> temp(n);
    for (long long i = 0; i < (long long)fa.size(); ++i) {
        temp[i] = int64_t (fa[i].real() + 0.5);
    }
    // Не забываем про переносы в старшие разряды:
    int64_t carry = 0;
    for (long long i = 0; i < n || carry > 0; ++i) {
        if (i >= n) temp.push_back(0);
        temp[i] += carry;
        carry = temp[i] / 1000;
        temp[i] -= carry * 1000;
        assert(temp[i] >= 0);
    }
    // Формируем ответ:
    std::vector<long long> res;
    res.reserve(this->digits.size() + other.digits.size());

    for (long long i = 0; i < n; i += 3) {
        long long c = temp[i];
        long long b = i+1 < n ? temp[i+1] : 0;
        long long a = i+2 < n ? temp[i+2] : 0;
        res.push_back(c + 1000 * (b + 1000 * a));
    }
    return UInt(res);
}

// Комбинированный метод умножения:
UInt UInt::mult(const UInt& other) const {
// Выбор метода умножения:
    long long len1 = (long long)this->digits.size();
    long long len2 = (long long)other.digits.size();
    long long temp = 3 * std::max(len1, len2);
    long long pow = 1;
    while (pow < temp) pow *= 2;
    pow *= 2;
    long long op1 = len1 * len2;
    long long op2 = 3 * pow * std::log(pow) / std::log(2);
    return op1 >= 15 * op2 ? fast_mult(other) : slow_mult(other);
}

// Деление на короткое:
UInt& UInt::operator/=(const long long num) {
    assert(num > 0);
    if (num >= BASE) {
        return *this /= UInt(num);
    }
    int64_t rem = 0;
    for (long long j = (long long)digits.size()-1; j >= 0; --j) {
        (rem *= BASE) += digits[j];
        auto div = rem / num;
        digits[j] = div;
        rem -= div * num;
    }
    return this->normalize();
}

// Остаток от деления на короткое:
long long operator%(const UInt& a, const long long num) {
    assert(num > 0);
    int64_t rem = 0;
    for (long long i = (long long)a.digits.size()-1; i >= 0; --i) {
        ((rem *= UInt::BASE) += a.digits[i]) %= num;
    }
    return rem;
}




// Целая часть и остаток от деления:
std::pair<UInt, UInt> UInt::div_mod(const UInt& other) const {
    if (other.digits.size() == 1u) {
        return {std::move(*this / other.digits[0]), *this % other.digits[0]};
    }
    const long long norm = BASE / (other.digits.back() + 1);
    const UInt a = *this * norm;
    const UInt b = other * norm;
    const long long a_size = (long long)a.digits.size();
    const long long b_size = (long long)b.digits.size();
    UInt q, r;
    q.digits.resize(a_size);
    for (long long i = a_size - 1; i >= 0; --i) {
        r *= BASE;
        r += a.digits[i];
        long long s1 = (long long)r.digits.size() <= b_size ? 0 : r.digits[b_size];
        long long s2 = (long long)r.digits.size() <= b_size - 1 ? 0 : r.digits[b_size - 1];
        long long d = (1LL * BASE * s1 + s2) / b.digits.back();
        auto temp = b * d;
        while (r < temp) {
            r += b;
            --d;
        }
        r -= temp;
        q.digits[i] = d;
    }
    return {std::move(q.normalize()), std::move(r /= norm)};
}

// Сравнение: result < 0 (меньше), result == 0 (равно), result > 0 (больше)
long long UInt::compare(const UInt& other) const {
    if (this->digits.size() > other.digits.size()) return 1;
    if (this->digits.size() < other.digits.size()) return -1;
    for (long long i = (long long)digits.size()-1; i >= 0; --i) {
        if (this->digits[i] > other.digits[i]) return 1;
        if (this->digits[i] < other.digits[i]) return -1;
    }
    return 0;
}

// Операторы сравнения:
bool operator< (const UInt& a, const UInt& b) { return a.compare(b) < 0; }
bool operator> (const UInt& a, const UInt& b) { return a.compare(b) > 0; }
bool operator==(const UInt& a, const UInt& b) { return a.compare(b) == 0; }
bool operator<=(const UInt& a, const UInt& b) { return a.compare(b) <= 0; }
bool operator>=(const UInt& a, const UInt& b) { return a.compare(b) >= 0; }
bool operator!=(const UInt& a, const UInt& b) { return a.compare(b) != 0; }

// Ввод из потока:
std::istream& operator>>(std::istream& is, UInt& number) {
    std::string s;
    is >> s;
    number = UInt(s);
    return is;
}

// Вывод в поток:
std::ostream& operator<<(std::ostream& os, const UInt& number) {
    os << number.digits.back();
    for (long long i = (long long)number.digits.size()-2; i >= 0; --i) {
        os << std::setw(UInt::WIDTH) << std::setfill('0') << number.digits[i];
    }
    return os << std::setfill(' ');
}

// Сумма:
UInt operator+(const UInt& a, const UInt& b) {
    return UInt(a) += b;
}

// Разность:
UInt operator-(const UInt& a, const UInt& b) {
    return UInt(a) -= b;
}

// Произведение:
UInt operator*(const UInt& a, const UInt& b) {
    return a.mult(b);
}

// Деление:
UInt operator/(const UInt& a, const UInt& b) {
    return a.div_mod(b).first;
}

// Взятие остатка:
UInt operator%(const UInt& a, const UInt& b) {
    return a.div_mod(b).second;
}

// Умножение:
UInt& UInt::operator*=(const UInt& other) {
    return *this = *this * other;
}

// Деление с присваиванием:
UInt& UInt::operator/=(const UInt& other) {
    return *this = *this / other;
}

// Взятие остатка с присваиванием:
UInt& UInt::operator%=(const UInt& other) {
    return *this = *this % other;
}

UInt operator+(const UInt& a, const long long b) { return UInt(a) += b; }
UInt operator+(const long long a, const UInt& b) { return b + a; }
UInt operator-(const UInt& a, const long long b) { return UInt(a) -= b; }
UInt operator*(const UInt& a, const long long b) { return UInt(a) *= b; }
UInt operator*(const long long a, const UInt& b) { return b * a; }
UInt operator/(const UInt& a, const long long b) { return UInt(a) /= b; }
UInt operator^(const UInt& a, const long long n) { return pow(a, n); } // Возведение в степень

//static const UInt prime = pow(UInt(2), 256) - pow(UInt(2), 224) + pow(UInt(2), 192) + pow(UInt(2), 96) - 1;



// Возведение в степень:
UInt pow(UInt a, long long n) {
    UInt res = 1;
    while (n > 0) {
        if (n % 2 != 0) res *= a;
        a *= a;
        n /= 2;
    }
    return res;
}





typedef std::complex<double> dou_cpx;

void fft(std::vector<dou_cpx>& a, bool invert) {
    int n = (int) a.size();
    if (n == 1)  return;

    std::vector<dou_cpx> a0(n/2),  a1(n/2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft (a0, invert); fft (a1, invert);

    double ang = 2 * M_PI/n * (invert ? -1 : 1);
    dou_cpx w(1),  wn(cos(ang), sin(ang));
    for (int i = 0; i < n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) a[i] /= 2,  a[i + n/2] /= 2;
        w *= wn;
    }
}

std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<dou_cpx> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft (fa, false),  fft (fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] *= fb[i];
    fft (fa, true);

    std::vector<int> res(n);
    for (size_t i = 0; i < n; ++i) res[i] = int (fa[i].real() + 0.5);

    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
    return res;
}

int main() {
    std::string s1, s2;
    std::vector<int> a, b;
    getline(std::cin, s1);
    getline(std::cin, s2);
    for (auto elem : s1) a.push_back(elem - '0');
    for (auto elem : s2) b.push_back(elem - '0');
    UInt a2{s1}, b2{s2};
    auto answer2 = a2 * b2;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    auto answer = multiply(a, b);
    std::reverse(answer.begin(), answer.end());

    std::cout << "PYK";

    int k;
    for (k = 0; k < answer.size(); ++k) if (answer[k] != 0) break;
    std::string answer_string= "";
    for (int i = k; i < answer.size(); ++i) answer_string + answer[i];

    UInt A2{answer_string};
    if (A2 == answer2) std::cout << "YES";
    else {
        std::cout << "NO";
        std::cout << A2 << "\n" << answer_string << "\n" << answer2;
    }
    return 0;
}

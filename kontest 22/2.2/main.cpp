#include <iostream>
#include <vector>
#include <string>


int color_to_int(char a) {
    if (a == 'R') return 1;
    if (a == 'G') return 2;
    if (a == 'B') return 3;
    return 0;
}

int find_third_color(int c1, int c2) {
    for (int color : {1, 2, 3}) {
        if (color != c1 && color != c2) {
            return color;
        }
    }
    return 0;
}

class Vertex {
private:
    int num;
    int color1;
    int color2;
    bool marked;

public:
    Vertex() {}

    Vertex(int color, int i) {
        num = i;
        this->color1 = color;
        this->color2 = 0;
    }

    bool try_repaint(int color, std::vector<std::vector<int>>& g, std::vector<Vertex>& vertex) {
        marked = true;
        if (color == color1 /*|| color == 0*/) {
            return false;
        } else {
            int c = color2;
            color2 = color;
            bool ok = true;
            for (int j : g[num]) {
                Vertex& v = vertex[j];
                if (v.marked) {
                    if (v.color2 == color) ok = false;
                } else if (v.color1 != color &&
                           !v.try_repaint(find_third_color(v.color1, color), g, vertex)) ok = false;
            }
            if (!ok) color2 = c;
            return ok;
        }
    }

    int get_new_color() const {
        return color2;
    }

    void print_new_color() const {
        if (color2 == 1) {
            std::cout << "R";
        } else if (color2 == 2) {
            std::cout << "G";
        } else if (color2 == 3) {
            std::cout << "B";
        } else std::cout << 0;
    }

    void change_marked (bool a) {
        marked = a;
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;

    std::vector<Vertex> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = Vertex(color_to_int(s[i]), i);
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    for (int i = 0; i < n; ++i) {
        if (v[i].get_new_color() == 0) {
            for (int color : {1, 2 ,3}) {
                for (Vertex& vertex : v) vertex.change_marked(false);
                if (v[i].try_repaint(color, g, v)) break;
            }
        }
    }

    bool all_repainted = true;
    for (const Vertex& vertex : v) {
        if (vertex.get_new_color() == 0) {
            all_repainted = false; break;
        }
    }

    if (all_repainted) {
        for (const Vertex& vertex : v) {
            vertex.print_new_color();
        }
    } else std::cout << "Impossible";
}


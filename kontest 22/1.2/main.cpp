
#ifndef OR_TOOLS_GRAPH_CLIQUES_H_
#define OR_TOOLS_GRAPH_CLIQUES_H_

#include <cstdint>
#include <functional>
#include <limits>
#include <numeric>
#include <vector>


namespace operations_research {

    void FindCliques(std::function<bool(int, int)> graph, int node_count,
                     std::function<bool(const std::vector<int>&)> callback);

    void CoverArcsByCliques(std::function<bool(int, int)> graph, int node_count,
                            std::function<bool(const std::vector<int>&)> callback);


    enum class CliqueResponse {

        STOP
    };


    enum class BronKerboschAlgorithmStatus {

        COMPLETED,

        INTERRUPTED
    };


    template <typename NodeIndex>
    class BronKerboschAlgorithm {
    public:

        using IsArcCallback = std::function<bool(NodeIndex, NodeIndex)>;

        using CliqueCallback =
        std::function<CliqueResponse(const std::vector<NodeIndex>&)>;


        BronKerboschAlgorithm(IsArcCallback is_arc, NodeIndex num_nodes,
                              CliqueCallback clique_callback)
                : is_arc_(std::move(is_arc)),
                  clique_callback_(std::move(clique_callback)),
                  num_nodes_(num_nodes) {}


        BronKerboschAlgorithmStatus Run();


        BronKerboschAlgorithmStatus RunIterations(int64_t max_num_iterations);


        BronKerboschAlgorithmStatus RunWithTimeLimit(int64_t max_num_iterations,
                                                     TimeLimit* time_limit);

        BronKerboschAlgorithmStatus RunWithTimeLimit(TimeLimit* time_limit) {
            return RunWithTimeLimit(std::numeric_limits<int64_t>::max(), time_limit);
        }

    private:
        DEFINE_INT_TYPE(CandidateIndex, ptrdiff_t);

        struct State {
            State() {}
            State(const State& other)
                    : pivot(other.pivot),
                      num_remaining_candidates(other.num_remaining_candidates),
                      candidates(other.candidates),
                      first_candidate_index(other.first_candidate_index),
                      candidate_for_recursion(other.candidate_for_recursion) {}

            State& operator=(const State& other) {
                pivot = other.pivot;
                num_remaining_candidates = other.num_remaining_candidates;
                candidates = other.candidates;
                first_candidate_index = other.first_candidate_index;
                candidate_for_recursion = other.candidate_for_recursion;
                return *this;
            }

            inline void MoveFirstCandidateToNotSet() {
                ++first_candidate_index;
                --num_remaining_candidates;
            }

            std::string DebugString() {
                std::string buffer;
                absl::StrAppend(&buffer, "pivot = ", pivot,
                                "\nnum_remaining_candidates = ", num_remaining_candidates,
                                "\ncandidates = [");
                for (CandidateIndex i(0); i < candidates.size(); ++i) {
                    if (i > 0) buffer += ", ";
                    absl::StrAppend(&buffer, candidates[i]);
                }
                absl::StrAppend(
                        &buffer, "]\nfirst_candidate_index = ", first_candidate_index.value(),
                        "\ncandidate_for_recursion = ", candidate_for_recursion.value());
                return buffer;
            }

            NodeIndex pivot;
            int num_remaining_candidates;
            absl::StrongVector<CandidateIndex, NodeIndex> candidates;
            CandidateIndex first_candidate_index;

            CandidateIndex candidate_for_recursion;
        };

        static const double kPushStateDeterministicTimeSecondsPerCandidate;

        void Initialize();

        void PopState();

        void PushState(NodeIndex selected);

        void InitializeState(State* state);

        inline bool IsArc(NodeIndex node1, NodeIndex node2) const {
            return node1 == node2 || is_arc_(node1, node2);
        }

        CandidateIndex SelectCandidateIndexForRecursion(State* state);

        std::string CliqueDebugString(const std::vector<NodeIndex>& clique);

        IsArcCallback is_arc_;

        CliqueCallback clique_callback_;

        const NodeIndex num_nodes_;

        std::vector<State> states_;

        std::vector<NodeIndex> current_clique_;

        int64_t num_remaining_iterations_;

        TimeLimit* time_limit_;
    };

    template <typename NodeIndex>
    void BronKerboschAlgorithm<NodeIndex>::InitializeState(State* state) {
        DCHECK(state != nullptr);
        const int num_candidates = state->candidates.size();
        int num_disconnected_candidates = num_candidates;
        state->pivot = 0;
        CandidateIndex pivot_index(-1);
        for (CandidateIndex pivot_candidate_index(0);
             pivot_candidate_index < num_candidates &&
             num_disconnected_candidates > 0;
             ++pivot_candidate_index) {
            const NodeIndex pivot_candidate = state->candidates[pivot_candidate_index];
            int count = 0;
            for (CandidateIndex i(state->first_candidate_index); i < num_candidates;
                 ++i) {
                if (!IsArc(pivot_candidate, state->candidates[i])) {
                    ++count;
                }
            }
            if (count < num_disconnected_candidates) {
                pivot_index = pivot_candidate_index;
                state->pivot = pivot_candidate;
                num_disconnected_candidates = count;
            }
        }
        state->num_remaining_candidates = num_disconnected_candidates;
        if (pivot_index >= state->first_candidate_index) {
            std::swap(state->candidates[pivot_index],
                      state->candidates[state->first_candidate_index]);
            ++state->num_remaining_candidates;
        }
    }

    template <typename NodeIndex>
    typename BronKerboschAlgorithm<NodeIndex>::CandidateIndex
    BronKerboschAlgorithm<NodeIndex>::SelectCandidateIndexForRecursion(
            State* state) {
        DCHECK(state != nullptr);
        CandidateIndex disconnected_node_index =
                std::max(state->first_candidate_index, state->candidate_for_recursion);
        while (disconnected_node_index < state->candidates.size() &&
               state->candidates[disconnected_node_index] != state->pivot &&
               IsArc(state->pivot, state->candidates[disconnected_node_index])) {
            ++disconnected_node_index;
        }
        state->candidate_for_recursion = disconnected_node_index;
        return disconnected_node_index;
    }

    template <typename NodeIndex>
    void BronKerboschAlgorithm<NodeIndex>::Initialize() {
        DCHECK(states_.empty());
        states_.reserve(num_nodes_);
        states_.emplace_back();

        State* const root_state = &states_.back();
        root_state->first_candidate_index = 0;
        root_state->candidate_for_recursion = 0;
        root_state->candidates.resize(num_nodes_, 0);
        std::iota(root_state->candidates.begin(), root_state->candidates.end(), 0);
        root_state->num_remaining_candidates = num_nodes_;
        InitializeState(root_state);

        DVLOG(2) << "Initialized";
    }

    template <typename NodeIndex>
    void BronKerboschAlgorithm<NodeIndex>::PopState() {
        DCHECK(!states_.empty());
        states_.pop_back();
        if (!states_.empty()) {
            State* const state = &states_.back();
            current_clique_.pop_back();
            state->MoveFirstCandidateToNotSet();
        }
    }

    template <typename NodeIndex>
    std::string BronKerboschAlgorithm<NodeIndex>::CliqueDebugString(
            const std::vector<NodeIndex>& clique) {
        std::string message = "Clique: [ ";
        for (const NodeIndex node : clique) {
            absl::StrAppend(&message, node, " ");
        }
        message += "]";
        return message;
    }

    template <typename NodeIndex>
    void BronKerboschAlgorithm<NodeIndex>::PushState(NodeIndex selected) {
        DCHECK(!states_.empty());
        DCHECK(time_limit_ != nullptr);
        DVLOG(2) << "PushState: New depth = " << states_.size() + 1
                 << ", selected node = " << selected;
        absl::StrongVector<CandidateIndex, NodeIndex> new_candidates;

        State* const previous_state = &states_.back();
        const double deterministic_time =
                kPushStateDeterministicTimeSecondsPerCandidate *
                previous_state->candidates.size();
        time_limit_->AdvanceDeterministicTime(deterministic_time, "PushState");

        new_candidates.reserve(previous_state->candidates.size());
        for (CandidateIndex i(0); i < previous_state->first_candidate_index; ++i) {
            const NodeIndex candidate = previous_state->candidates[i];
            if (IsArc(selected, candidate)) {
                new_candidates.push_back(candidate);
            }
        }
        const CandidateIndex new_first_candidate_index(new_candidates.size());
        for (CandidateIndex i = previous_state->first_candidate_index + 1;
             i < previous_state->candidates.size(); ++i) {
            const NodeIndex candidate = previous_state->candidates[i];
            if (IsArc(selected, candidate)) {
                new_candidates.push_back(candidate);
            }
        }

        current_clique_.push_back(selected);
        if (new_candidates.empty()) {
            DVLOG(2) << CliqueDebugString(current_clique_);
            const CliqueResponse response = clique_callback_(current_clique_);
            if (response == CliqueResponse::STOP) {
                num_remaining_iterations_ = 1;
            }
            current_clique_.pop_back();
            previous_state->MoveFirstCandidateToNotSet();
            return;
        }

        states_.emplace_back();
        State* const new_state = &states_.back();
        new_state->candidates.swap(new_candidates);
        new_state->first_candidate_index = new_first_candidate_index;

        InitializeState(new_state);
    }

    template <typename NodeIndex>
    BronKerboschAlgorithmStatus BronKerboschAlgorithm<NodeIndex>::RunWithTimeLimit(
            int64_t max_num_iterations, TimeLimit* time_limit) {
        CHECK(time_limit != nullptr);
        time_limit_ = time_limit;
        if (states_.empty()) {
            Initialize();
        }
        for (num_remaining_iterations_ = max_num_iterations;
             !states_.empty() && num_remaining_iterations_ > 0 &&
             !time_limit->LimitReached();
             --num_remaining_iterations_) {
            State* const state = &states_.back();
            DVLOG(2) << "Loop: " << states_.size() << " states, "
                     << state->num_remaining_candidates << " candidate to explore\n"
                     << state->DebugString();
            if (state->num_remaining_candidates == 0) {
                PopState();
                continue;
            }

            const CandidateIndex selected_index =
                    SelectCandidateIndexForRecursion(state);
            DVLOG(2) << "selected_index = " << selected_index;
            const NodeIndex selected = state->candidates[selected_index];
            DVLOG(2) << "Selected candidate = " << selected;

            NodeIndex& f = state->candidates[state->first_candidate_index];
            NodeIndex& s = state->candidates[selected_index];
            std::swap(f, s);

            PushState(selected);
        }
        time_limit_ = nullptr;
        return states_.empty() ? BronKerboschAlgorithmStatus::COMPLETED
                               : BronKerboschAlgorithmStatus::INTERRUPTED;
    }

    template <typename NodeIndex>
    BronKerboschAlgorithmStatus BronKerboschAlgorithm<NodeIndex>::RunIterations(
            int64_t max_num_iterations) {
        TimeLimit time_limit(std::numeric_limits<double>::infinity());
        return RunWithTimeLimit(max_num_iterations, &time_limit);
    }

    template <typename NodeIndex>
    BronKerboschAlgorithmStatus BronKerboschAlgorithm<NodeIndex>::Run() {
        return RunIterations(std::numeric_limits<int64_t>::max());
    }

    template <typename NodeIndex>
    const double BronKerboschAlgorithm<
            NodeIndex>::kPushStateDeterministicTimeSecondsPerCandidate = 0.54663e-7;
}  // namespace operations_research

#endif  // OR_TOOLS_GRAPH_CLIQUES_H_
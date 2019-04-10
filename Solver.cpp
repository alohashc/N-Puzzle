//
// Created by aloha on 22.03.19.
//

#include "Solver.hpp"

Solver::Solver(Field *start) {
    init(start);
    aStar();
}

Solver::~Solver() {

}

void Solver::printT(State *s) {
    for (int i = 0; i < field->getSize(); ++i) {

        std::cout << s->tiles[i].value << " ";
        if ((i + 1) % field->getRows()  == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << s->f << std::endl;
    std::cout << "____________________" << std::endl;
}

void Solver::exitAndOutput(State *node) {
    std::list<std::string>::iterator	it;

    while (node->parent)
    {
        ++moves;
        output.push_front(print(node->tiles));
        node = node->parent;
    }
    for (const auto &it : output)
    {
        std::cout << it << std::endl;
    }
    std::cout << "Complexity in time: \033[1;32m" << totalOpenedSets << "\033[0m" << std::endl;
    std::cout << "Complexity in size: \033[1;32m" << maxOpenedSets << "\033[0m" << std::endl;
    std::cout << "Number of moves required to transition from the initial state to the final state: " <<
                 "\033[1;32m" << moves << "\033[0m" << std::endl;


    throw "Puzzle solved.";
}

void Solver::swapTiles(Tile &old_pos, Tile &new_pos) {
    auto tmp = old_pos.end_pos;

    old_pos.value = new_pos.value;
    new_pos.value = 0;
    old_pos.end_pos = new_pos.end_pos;
    new_pos.end_pos = tmp;
}

void Solver::createChildState(State* state, int gap_pos, int new_pos) {
    auto *tiles = new Tile[field->getSize()];
    State new_state;

    std::copy(state->tiles, state->tiles + field->getSize(), tiles);
    swapTiles(tiles[gap_pos], tiles[new_pos]);
    new_state.parent = nullptr;
    new_state.tiles = tiles;
    new_state.hash = genHash(new_state.tiles);
    new_state.gap_pos = new_pos;
    new_state.h = field->getHeuristic(new_state.tiles);
    new_state.g = state->g + 1;
    new_state.f = new_state.g + new_state.h;
    state->children.push_back(new_state);
}

void Solver::getChildren(State *state) {
    int up = state->gap_pos - field->getRows();
    int down = state->gap_pos + field->getRows();
    int prev = state->gap_pos - 1;
    int next = state->gap_pos + 1;

    if (up >= 0)
        createChildState(state, state->gap_pos, up);
    if (down < field->getSize())
        createChildState(state, state->gap_pos, down);

    if (next < field->getSize() && next / field->getRows() == state->gap_pos / field->getRows())
        createChildState(state, state->gap_pos, next);
    if (prev >= 0 && prev / field->getRows() == state->gap_pos / field->getRows())
        createChildState(state, state->gap_pos, prev);
}

void Solver::aStar() {
    State curr;

    while (!queue.empty()) {

        curr = queue.top();
        printT(&curr);
        queue.pop();

        if (curr.hash == hash_end)
            exitAndOutput(&curr);
        open.erase(curr.hash);
        closed.emplace(curr.hash, curr.f);

        getChildren(&curr);
        for (auto it : curr.children) {
            if (!isExists(open, it) && !isExists(closed, it)) {
                it.parent = new State(curr);
                queue.push(it);
                open.emplace(it.hash, it.f);
                ++totalOpenedSets;
                maxOpenedSets = std::max(maxOpenedSets, static_cast<int>(queue.size()));
            }
        }
    }
}

std::string Solver::genHash(Tile *tiles) {
    std::string hash_str;

    for (int i = 0; i < field->getSize(); ++i) {
        hash_str += std::to_string(tiles[i].value) + ',';
    }

    return hash_str;
}

bool Solver::isExists(std::map<std::string, int>& collection, State & state) {

    const auto it = collection.find(state.hash);
    if (it == collection.end())
        return false;

    if (it->second > state.f)
    {
        collection.erase(it);
        return false;
    }
    return true;
}

void Solver::init(Field *fieldIn) {
    State start;

    field = fieldIn;
    hash_end = field->genHashEnd();
    start.parent = nullptr;
    start.tiles = field->getTiles();
    start.gap_pos = field->getGapPos();
    start.hash = genHash(start.tiles);
    start.g = 0;
    start.h = field->getHeuristic(start.tiles);
    start.f = start.g + start.h;
    queue.push(start);
    open.emplace(genHash(start.tiles), start.f);
    ++totalOpenedSets;
    maxOpenedSets = 1;
}

std::string			Solver::print(Tile * state)
{
    std::string str;

    for (int i = 0; i < field->getSize(); ++i) {
        if (i % field->getRows())
            str += "\t";
        else
            str += "\n";
        if (!state[i].value)
            str += " ";
        else
            str += std::to_string(state[i].value);
    }
    return (str);
}
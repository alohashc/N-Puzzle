//
// Created by aloha on 22.03.19.
//

#include "Solver.hpp"

Solver::Solver(Field *start) {
    this->init(start);
    this->aStar();
}

Solver::~Solver() {

}

void Solver::printT(s_state *s) {
    for (int i = 0; i < this->field->getSize(); ++i) {

        std::cout << s->tiles[i].value << " ";
        if ((i + 1) % this->field->getRows()  == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << s->f << std::endl;
    std::cout << "____________________" << std::endl;
}

void Solver::exitAndOutput(s_state *node) {
    std::list<std::string>::iterator	it;

    while (node->parent)
    {
        ++this->moves;
        this->_output.push_front(this->print(node->tiles));
        node = node->parent;
    }
    for ( it = this->_output.begin(); it != this->_output.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "Complexity in time: \033[1;32m" << this->totalOpenedSets << "\033[0m" << std::endl;
    std::cout << "Complexity in size: \033[1;32m" << this->maxOpenedSets << "\033[0m" << std::endl;
    std::cout << "Number of moves required to transition from the initial state to the final state: " <<
                 "\033[1;32m" << this->moves << "\033[0m" << std::endl;


    exit(0);
}

void Solver::swapTiles(s_tile &old_pos, s_tile &new_pos) {
    auto tmp = old_pos.end_pos;

    old_pos.value = new_pos.value;
    new_pos.value = 0;
    old_pos.end_pos = new_pos.end_pos;
    new_pos.end_pos = tmp;
}

void Solver::createChildState(s_state* state, int gap_pos, int new_pos) {
    auto *tiles = new s_tile[this->field->getSize()];
    s_state new_state;

    std::copy(state->tiles, state->tiles + this->field->getSize(), tiles);
    this->swapTiles(tiles[gap_pos], tiles[new_pos]);
    new_state.parent = nullptr;
    new_state.tiles = tiles;
    new_state.hash = this->genHash(new_state.tiles);
    new_state.gap_pos = new_pos;
    new_state.h = this->field->getHeuristic(new_state.tiles);
    new_state.g = state->g + 1;
    new_state.f = new_state.g + new_state.h;
    state->children.push_back(new_state);
}

void Solver::getChildren(s_state *state) {
    int up = state->gap_pos - this->field->getRows();
    int down = state->gap_pos + this->field->getRows();
    int prev = state->gap_pos - 1;
    int next = state->gap_pos + 1;

    if (up >= 0)
        this->createChildState(state, state->gap_pos, up);
    if (down < this->field->getSize())
        this->createChildState(state, state->gap_pos, down);

    if (next < field->getSize() && next / field->getRows() == state->gap_pos / field->getRows())
        this->createChildState(state, state->gap_pos, next);
    if (prev >= 0 && prev / field->getRows() == state->gap_pos / field->getRows())
        this->createChildState(state, state->gap_pos, prev);
}

bool Solver::isExists(std::map<std::string, int>& map, s_state & state) {
    std::map<std::string, int>::iterator	it;

    it = map.find(state.hash);
    if (it != map.end())
    {
        if (state.f < (*it).second)
        {
            map.erase(it);
            return false;
        }
        return true;
    }
    return false;
}

void Solver::aStar() {
    s_state curr;

    while (!this->queue.empty()) {

        curr = this->queue.top();
        this->printT(&curr);
        this->queue.pop();

        if (curr.hash == this->hash_end)
            this->exitAndOutput(&curr);
        this->open.erase(curr.hash);
        this->closed.emplace(curr.hash, curr.f);

        this->getChildren(&curr);
        for (auto it : curr.children) {
            if (!this->isExists(this->open, it) && !this->isExists(this->closed, it)) {
                it.parent = new s_state(curr);
                this->queue.push(it);
                this->open.emplace(it.hash, it.f);
                ++totalOpenedSets;
                maxOpenedSets = std::max(maxOpenedSets, static_cast<int>(this->open.size()));
            }
        }
    }
}

std::string Solver::genHash(s_tile *tiles) {
    std::string hash_str;

    for (int i = 0; i < this->field->getSize(); ++i) {
        hash_str += std::to_string(tiles[i].value) + ',';
    }

    return hash_str;
}

void Solver::init(Field *field) {
    s_state start;

    this->field = field;
    this->hash_end = field->genHashEnd();
    start.parent = nullptr;
    start.tiles = field->getTiles();
    start.gap_pos = field->getGapPos();
    start.hash = this->genHash(start.tiles);
    start.g = 0;
    start.h = field->getHeuristic(start.tiles);
    start.f = start.g + start.h;
    this->queue.push(start);
    this->open.emplace(this->genHash(start.tiles), start.f);
    ++totalOpenedSets;
    maxOpenedSets = 1;
}

std::string			Solver::print(s_tile * state)
{
    std::stringstream	out;


    for (int i = 0; i < this->field->getSize(); ++i)
    {
        (i % this->field->getRows()) ? out << "\t" : out << std::endl;
        if (!state[i].value)
        {
            out << " ";
        }
        else
        {
            out << state[i].value;
        }
    }
    return (out.str());
}
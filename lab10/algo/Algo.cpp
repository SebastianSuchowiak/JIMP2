//
// Created by sebastian on 15.05.18.
//

#include "Algo.h"


bool algo::Contains(const std::vector<int> &v, int element) {
    return std::find(v.begin(), v.end(), element) != v.end();
}

std::set<std::string> algo::Keys(const std::map<std::string, int> &m) {

    std::set<std::string> result;

    std::transform(m.begin(), m.end(), std::inserter(result, result.begin()),
                   [](const auto &current) {
                       return current.first;
                   });

    return result;
}

std::vector<int> algo::Values(const std::map<std::string, int> &m) {

    std::vector<int> result;

    std::transform(m.begin(), m.end(), std::back_inserter(result),
                   [](const auto &current) {
                       return current.second;
                   });

    return result;
}

bool algo::ContainsKey(const std::map<std::string, int> &v, const std::string &key) {
    return v.find(key) != v.end();
}

bool algo::ContainsValue(const std::map<std::string, int> &v, int value) {
    std::vector<int> values = Values(v);
    return Contains(values, value);
}

void algo::SortInPlace(std::vector<int> *v) {
    std::sort(v->begin(), v->end());
}

std::vector<int> algo::Sort(const std::vector<int> &v) {
    std::vector<int> result = v;
    std::sort(result.begin(), result.end());
    return result;
}

void algo::SortByFirstInPlace(std::vector<std::pair<int, int>> *v) {
    std::sort(v->begin(), v->end(),
              [](std::pair<int, int> left, std::pair<int, int> right) {
                  return left.first < right.first;
              });
}

void algo::SortBySecondInPlace(std::vector<std::pair<int, int>> *v) {
    std::sort(v->begin(), v->end(),
              [](std::pair<int, int> left, std::pair<int, int> right) {
                  return left.second < right.second;
              });
}

void algo::SortByThirdInPlace(std::vector<std::tuple<int, int, int>> *v) {
    std::sort(v->begin(), v->end(),
              [](std::tuple<int, int, int> left, std::tuple<int, int, int> right) {
                  return std::get<2>(left) < std::get<2>(right);
              });
}

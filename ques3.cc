#include <algorithm>
#include <print>
#include <set>
#include <tuple>
#include <vector>

void make_set(std::vector<int> &names, std::vector<int> &ranks)
{
    for (int i = 0; i < names.size(); i++)
    {
        ranks[i] = 1;
        names[i] = i;
    }
}

int find_name(int node, std::vector<int> &p)
{
    if (node == p[node])
        return node;

    return p[node] = find_name(p[node], p);
}

void union_set(int u, int v, std::vector<int> &names, std::vector<int> &rank)
{
    int name_u = find_name(u, names);
    int name_v = find_name(v, names);

    if (rank[name_u] < rank[name_v])
    {
        names[name_u] = name_v;
    }
    else if (rank[name_v] < rank[name_u])
    {
        names[name_v] = name_u;
    }
    else
    {
        names[name_v] = name_u;
        rank[name_u]++;
    }
}

std::set<std::tuple<int, int>> kruskals_algo(std::vector<std::tuple<int, int, int>> &edges, int n)
{
    std::vector<int> names(n);
    std::vector<int> rank(n);
    make_set(names, rank);

    std::sort(edges.begin(), edges.end(), [](auto const &a, auto const &b) { return std::get<2>(a) < std::get<2>(b); });

    std::set<std::tuple<int, int>> A;
    int min_weight = 0;

    for (auto &[u, v, w] : edges)
    {
        if (find_name(u, names) != find_name(v, names))
        {
            A.insert({u, v});

            min_weight += w;
            union_set(u, v, names, rank);
        }
    }

    std::println("Minimum Wieght is: {}", min_weight);
    return A;
}

int main(int argc, char *argv[])
{
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}, {3, 4, 7}};

    auto mst = kruskals_algo(edges, 5);

    std::println("MST edges");
    for (auto [u, v] : mst)
    {
        std::println("{} - {}", u, v);
    }
}

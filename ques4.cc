#include <climits>
#include <cstddef>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>

class Vertex
{
  public:
    Vertex *parent;
    int distance;
    std::string name;
    int d, f;

    Vertex(Vertex *p, int d, std::string n) : parent(p), distance(d), name(n), d(0), f(0)
    {
    }
};

void initialize_single_source(std::unordered_map<Vertex *, std::vector<std::tuple<Vertex *, int>>> &adj, Vertex &s)
{
    for (auto &[v, _] : adj)
    {
        v->parent = NULL, v->distance = INT_MAX;
    }
    s.distance = 0;
}

void relax(Vertex &u, Vertex &v, int w)
{
    if (u.distance != INT_MAX && v.distance > u.distance + w)
    {
        v.parent = &u;
        v.distance = u.distance + w;
    }
}

bool bellman_ford(std::unordered_map<Vertex *, std::vector<std::tuple<Vertex *, int>>> &adj, Vertex &s,
                  int vertices_count)
{
    initialize_single_source(adj, s);

    for (int i = 0; i < vertices_count - 1; i++)
    {
        for (auto &[v, edges] : adj)
        {
            for (auto &[u, w] : edges)
            {
                relax(*v, *u, w);
            }
        }
    }

    for (auto &[u, edges] : adj)
    {
        for (auto &[v, w] : edges)
        {
            if (v->distance > u->distance + w)
            {
                return false;
            }
        }
    }
    return true;
}

void print_path(Vertex *source, Vertex *destination)
{
    if (source == destination)
    {
        std::print("{} ", destination->name);
    }
    else if (destination->parent == NULL)
        std::println("No path from {} to {}", source->name, destination->name);
    else
    {
        print_path(source, destination->parent);
        std::print("{} ", destination->name);
    }
}

void print_path_from_source_to_all(const std::vector<Vertex *> &list_of_vertices, Vertex *source)
{
    for (auto &v : list_of_vertices)
    {
        std::println("Path for {}", v->name);
        print_path(source, v);
        std::println();
    }
}

int main(int argc, char *argv[])
{
    Vertex S{NULL, INT_MAX, "S"}, T{NULL, INT_MAX, "T"}, X{NULL, INT_MAX, "X"}, Y{NULL, INT_MAX, "Y"},
        Z{NULL, INT_MAX, "Z"};

    std::unordered_map<Vertex *, std::vector<std::tuple<Vertex *, int>>> adj;

    adj[&S] = {{&T, 3}, {&Y, 5}};
    adj[&T] = {{&Y, 2}, {&X, 6}};
    adj[&X] = {{&Z, 2}};
    adj[&Y] = {{&T, 1}, {&Z, 6}, {&X, 4}};
    adj[&Z] = {{&S, 3}, {&X, 7}};

    bool ok = bellman_ford(adj, S, 5);
    if (ok)
    {
        std::println("No negative edges found");

        print_path_from_source_to_all({&S, &T, &X, &Y, &Z}, &S);
    }
    return 0;
}

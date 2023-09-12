/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"


using namespace std;

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    int min = INT_MAX;
    for (auto v : graph.getVertices()) {
        graph.setVertexLabel(v, "UNVISITED");
        for (auto near : graph.getAdjacent(v)) {
            graph.setEdgeLabel(v, near, "UNVISITED");
        }
    }
    queue<Vertex> q;
    Vertex start = graph.getStartingVertex();
    graph.setVertexLabel(start, "VISITED");
    q.push(start);

    while (!q.empty()){
        Vertex v = q.front();
        q.pop();
        for (auto w : graph.getAdjacent(v)) {
            if (graph.getVertexLabel(w) == "UNVISITED") {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q.push(w);
            } else if (graph.getEdgeLabel(v, w) == "UNVISITED") {
                graph.setEdgeLabel(v, w, "CROSS");
            }
            if (graph.getEdgeWeight(v, w) < min){ 
                min = graph.getEdgeWeight(v, w);
            }
        }
    }
    for (auto v : graph.getVertices()) {
        for (auto near : graph.getAdjacent(v)) {
            if (graph.getEdgeWeight(v, near) == min) {
                graph.setEdgeLabel(v, near, "MIN");
            }
        }
    }

    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */;
    unordered_map<Vertex, Vertex> parent; 
    //init
    for (auto v : graph.getVertices()) {
        graph.setVertexLabel(v, "UNVISITED");
        for (auto near : graph.getAdjacent(v)) {
            graph.setEdgeLabel(v, near, "UNVISITED");
        }
    }

    //bfs
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    while (!q.empty()){
        Vertex v = q.front();
        q.pop();
        if (v == end) break;        
        for (auto w : graph.getAdjacent(v)) {
            if (graph.getVertexLabel(w) == "UNVISITED") {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                parent[w] = v;
                q.push(w);
            } else if (graph.getEdgeLabel(v, w) == "UNVISITED") {
                graph.setEdgeLabel(v, w, "CROSS");
            }
        }
    }

    //backtrace
    int length = 0;
    Vertex v = end;
    while (v != start) {
        Vertex w = parent[v];
        graph.setEdgeLabel(v, w, "MINPATH");
        v = w;
        length++;
    }

    return length;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    DisjointSets forest;
    forest.addelements(graph.getVertices().size());
    unordered_map<Vertex, int> vertex_map;
    size_t idx = 0;
    for (auto v : graph.getVertices()){
        vertex_map[v] = idx;
        idx ++;
    }

    vector<Edge> edges;
    for (auto e : graph.getEdges()){
        edges.push_back(e);
    }
    sort(edges.begin(), edges.end(), compare_weight);
    size_t min_edges = graph.getVertices().size() - 1;
    
    size_t trav = 0;
    while (min_edges > 0 && trav < edges.size()){
        Edge e = edges[trav];
        if (forest.find(vertex_map[e.source]) != forest.find(vertex_map[e.dest])) {
            graph.setEdgeLabel(e.source, e.dest, "MST");
            forest.setunion(vertex_map[e.source], vertex_map[e.dest]);
            min_edges--;
        }
        trav ++;
    }
}

bool GraphTools::compare_weight(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}


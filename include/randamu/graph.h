/**
 * @file graph.h
 * @brief Defines structures and functions for two types of graphs: rd_csc_graph,
 * a CUDA-friendly sparse matrix representation (CSC: Compressed Sparse Column),
 * and rd_csc_graph, an adjacency list (using sorted arrays for the lists).
 */
#ifndef RANDAMU_GRAPH_H_
#define RANDAMU_GRAPH_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RANDAMU_CUDA
  typedef struct nvgraphCSCTopology32I_st rd_csc_graph;
#else
  typedef struct {
    int nvertices;
    int nedges;
    int *destination_offsets;
    int *source_indices;
  } rd_csc_graph;
#endif

/**
 * \brief A matrix as an adjacency list (using sorted arrays for faster lookup). Uses 'int' for better
 * compatibility with CUDA's graph type.
 */
typedef struct {
  int nvertices;    /**< Number of vertices (nodes). */
  int* nedges;      /**< Number of edges per vertex. */
  int* capacities;  /**< Memory capacity for each vertex set. */
  int** edges;      /**< The adjacency list, each vertex has a sorted array of neighbors. */
} rd_adj_graph;

void rd_csc_from_adj(rd_csc_graph* dest, const rd_adj_graph* source);

void rd_csc_graph_free(rd_csc_graph* g);

void rd_adj_graph_init(rd_adj_graph* g, const int nvertices);

void rd_adj_from_csc(rd_adj_graph* dest, const rd_csc_graph* source);

// [|V|, RANGES, EDGES]
int* rd_flat_from_adj(int** dest, const rd_adj_graph* src);

void rd_adj_graph_reserve(rd_adj_graph* g, const int vertex, const int new_capacity);

void rd_adj_graph_reserve_all(rd_adj_graph* g, const int new_capacity);

int rd_adj_graph_size(const rd_adj_graph* g);

int rd_adj_graph_add_edge(rd_adj_graph* g, const int source, const int dest);

int rd_adj_graph_del_edge(rd_adj_graph* g, const int source, const int dest);

int rd_adj_graph_has_edge(const rd_adj_graph *g, const int source, const int dest);

void rd_adj_graph_free(rd_adj_graph* g);

#ifdef __cplusplus
}
#endif

#endif


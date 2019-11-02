/**
 * @file graph.h
 * @brief Defines structures and functions for two types of graphs: r_csc_graph,
 * a CUDA-friendly sparse matrix representation (CSC: Compressed Sparse Column),
 * and r_csc_graph, an adjacency list (using sorted arrays for the lists).
 */
#ifndef RAW_GRAPH_H_
#define RAW_GRAPH_H_

#include "raw/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RAW_CUDA
  typedef struct nvgraphCSCTopology32I_st r_csc_graph;
#else
  typedef struct {
    int nvertices;
    int nedges;
    int *destination_offsets;
    int *source_indices;
  } r_csc_graph;
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
} r_adj_graph;

void r_csc_from_adj(r_csc_graph* dest, const r_adj_graph* source);

void r_csc_graph_free(r_csc_graph* g);

void r_adj_graph_init(r_adj_graph* g, const int nvertices);

void r_adj_from_csc(r_adj_graph* dest, const r_csc_graph* source);

// [|V|, RANGES, EDGES]
int* r_flat_from_adj(int** dest, const r_adj_graph* src);

void r_adj_graph_reserve(r_adj_graph* g, const int vertex, const int new_capacity);

void r_adj_graph_reserve_all(r_adj_graph* g, const int new_capacity);

int r_adj_graph_size(const r_adj_graph* g);

int r_adj_graph_add_edge(r_adj_graph* g, const int source, const int dest);

int r_adj_graph_del_edge(r_adj_graph* g, const int source, const int dest);

int r_adj_graph_has_edge(const r_adj_graph *g, const int source, const int dest);

void r_adj_graph_free(r_adj_graph* g);

#ifdef __cplusplus
}
#endif

#endif


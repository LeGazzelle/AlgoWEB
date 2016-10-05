//
// Created by Gabriele Santi on 05/10/16.
//

#include "GraphGen.hpp"

class RandomGenerator {
public:
    RandomGenerator(int max) {
        generator.seed((const uint32_t &) std::time(0));
        this->dist = boost::random::uniform_int_distribution<>(1, max);
    }

    int rand() {
        return this->dist(generator);
    }

private:
    //int seed;
    static boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> dist;
};

boost::random::mt19937 RandomGenerator::generator;

UndirectedGraph GraphGen::generate(int v, int e, int maxWeight) {
    //Initialize random generator

    int i, arr[10];

    RandomGenerator rand(100);

    for (i = 0; i < 10; i++)
        arr[i] = rand.rand();

    for (i = 0; i < 10; i++)
        std::cout << "rand" << i << ": " << arr[i] << "; ";

    return 0;
};

/* This function generates a random connected simple graph with
   v vertices and max(v-1,e) edges.  The graph can be weighted
   (weight_flag == 1) or unweighted (weight_flag != 1). If
   it is weighted, the weights are in the range 1 to max_wgt.
   It is assumed that e <= v(v-1)/2. (In this program, this assured
   because of the call to fix_imbalanced_graph.)

   To  generate  a  random  connected  graph,  we begin by
   generating  a  random  spanning  tree.  To generate a random
   spanning  tree,  we  first  generate  a  random  permutation
   tree[0],...,tree[v-1]. (v = number of vertices.)
   We  then  iteratively  add edges  to form a
   tree.  We  begin with the tree consisting of vertex tree[0] and
   no   edges.   At   the   iterative   step,  we  assume  that
   tree[0],tree[1],...,tree[i-1]  are  in  the  tree.  We  then add vertex
   tree[i]  to     the    tree    by    adding    the    edge
   (tree[i],tree[rand(i)]).  (This  construction  is similar to
   that  of  Prim's algorithm.) Finally, we add random edges to
   produce the desired number of edges.
 */
//void random_connected_graph( int v,
//                             int e,
//                             int max_wgt,
//                             int weight_flag,
//                             char* out_file )
//{
//   int i, j, count, index, *adj_matrix, *tree;
//
//   if ( ( adj_matrix = ( int * ) calloc( v * v, sizeof( int ) ) )
//        == NULL ) {
//      printf( "Not enough room for this size graph\n" );
//      return;
//   }
//
//   if ( ( tree = ( int * ) calloc( v, sizeof( int ) ) ) == NULL ) {
//      printf( "Not enough room for this size graph\n" );
//      free( adj_matrix );
//      return;
//   }
//
//   printf( "\n\tBeginning construction of graph.\n" );
//
//   /*  Generate a random permutation in the array tree. */
//   init_array( tree, v );
//   permute( tree, v );
//
//   /*  Next generate a random spanning tree.
//       The algorithm is:
//
//         Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
//         the tree.  Add an edge incident on tree[ i ]
//         and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
//    */
//
//   for ( i = 1; i < v; i++ ) {
//      j = ran( i );
//      adj_matrix[ tree[ i ] * v + tree[ j ] ] =
//         adj_matrix[ tree[ j ] * v + tree[ i ] ] =
//         weight_flag ? 1 + ran( max_wgt ) : 1;
//   }
//
//   /* Add additional random edges until achieving at least desired number */
//
//   for ( count = v - 1; count < e; ) {
//      i = ran( v );
//      j = ran( v );
//
//      if ( i == j )
//         continue;
//
//      if ( i > j )
//         swap( &i, &j );
//
//      index = i * v + j;
//      if ( !adj_matrix[ index ] ) {
//         adj_matrix[ index ] = weight_flag ? 1 + ran( max_wgt ) : 1;
//         count++;
//      }
//   }
//
//   print_graph( v, count, out_file, adj_matrix, Undirected );
//
//   free( tree );
//   free( adj_matrix );
//}


/* set a[ i ] = i, for i = 0,...,end - 1 */
void GraphGen::initArray(int *a, int end) {
    int i;

    for (i = 0; i < end; i++)
        *a++ = i;
}


/* randomly permute a[ 0 ],...,a[ n - 1 ] */
void GraphGen::permute(int *a, int n) {
//   int i;
//
//   for ( i = 0; i < n - 1; i++ )
//      swap( a + i + ran( n - i ), a + i );
}

void GraphGen::swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
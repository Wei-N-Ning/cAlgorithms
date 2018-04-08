
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <admSimpleGraph.h>
#include <admToStr.h>

static admSimpleGraph_t *createGraph(size_t workload, admSimpleNode_t **start) {
    size_t nbuf = 32;
    admSimpleGraph_t *G = CreateAdmSimpleGraph(workload);
    admSimpleNode_t *n = NULL;
    admSimpleNode_t **arr = malloc(workload * sizeof(admSimpleNode_t *));
    char buf[32];
    memset(buf, 0, nbuf);
    for (uint64_t i=0; i<workload; ++i) {
        BytesToUniqueString(i * 2 + 1, buf, nbuf);
        n = GetOrCreateLabelledNode(G, buf);
        arr[i] = n;
    }
    for (size_t i=0; i<workload; ++i) {
        n = arr[i];
        for (size_t idx = 0; idx<workload; idx = idx * 2 + 1) {
            AdmConnectTo(n, arr[(idx + 1 + i) % workload]);
        }
    }
    (*start) = arr[0];
    free(arr);
    return G;
}

static void _visitNode(admSimpleNode_t *n, admDFSState_t *state) {
    ;
}

static void _visitConn(admSimpleEdge_t *e, admDFSState_t *state) {
    ;
}

static void _DFS(admSimpleGraph_t *G, admSimpleNode_t *start, size_t sz) {
    admDFSState_t *state = CreateDFSState(sz);
    AdmGraphDFS(G, start, state, _visitNode, _visitConn);
    DeleteDFSState(state);
}

int main(int argc, char **argv) {
    size_t workloads[] = {
        100, 500, 1000, 5000,
        10000,
        50000,
        100000,
        500000
    };
    size_t workload = 0;
    admSimpleGraph_t *G = NULL;
    admSimpleNode_t *start = NULL;
    clock_t s, e;
    double msec;
    printf("# NumElements Time\n");
    for (size_t i=0; i<sizeof(workloads)/sizeof(size_t); ++i) {
        workload = workloads[i];
        G = createGraph(workload, &start);
        s = clock();
        _DFS(G, start, AdmGraphSize(G));
        e = clock();
        msec = e - s;
        printf("%d %f\n", (int)workload, msec);
        DeleteAdmSimpleGraph(G);
    }
    return 0;
}

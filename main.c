#include <stdio.h>
#include "graph.h"

int main()
{
    char input = 'z';
    pnode firstHead = NULL;
    pnode *head = &firstHead;
    int src = 0, dest = 0, answer_TSP = 0;

    while (scanf("%c", &input) != EOF)
    {
        switch (input)
        {
        case 'A':
            build_graph_cmd(head);
            break;

        case 'B':
            insert_node_cmd(head);
            break;

        case 'D':
            delete_node_cmd(head);
            break;

        case 'S':
            src = -1;
            dest = -1;
            scanf("%d", &src);
            scanf("%d", &dest);
            int answer_dijkstra = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", answer_dijkstra);
            break;

        case 'T':
            answer_TSP = TSP_cmd(head);
            printf("TSP shortest path: %d \n", answer_TSP);
            break;

        default:
            break;
        }
    }
    deleteGraph_cmd(head);
    return 0;
}

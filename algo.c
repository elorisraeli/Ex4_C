#include "graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INFINITY __INT_MAX__

typedef struct dijkstra_graph
{
    pnode node;
    int distance_from_root;
    int finish;
    struct dijkstra_graph *next;
} dijkstraG, *pdijkstraG;

pdijkstraG init_dijkstra_graph(pnode head, int src) //initialization
{
    pdijkstraG node_holder = NULL;
    pdijkstraG *temp_dijkstra_node = &node_holder;

    while (head != NULL)
    {
        (*temp_dijkstra_node) = (pdijkstraG)malloc(sizeof(dijkstraG));
        (*temp_dijkstra_node)->finish = 0;
        (*temp_dijkstra_node)->node = head;
        if (head->node_num == src)
        {
            (*temp_dijkstra_node)->distance_from_root = 0;
        }
        else
        {
            (*temp_dijkstra_node)->distance_from_root = INFINITY;
        }
        (*temp_dijkstra_node)->next = NULL;
        temp_dijkstra_node = &((*temp_dijkstra_node)->next);
        head = head->next;
    }
    return node_holder;
}

pdijkstraG get_dijkstra_node(pdijkstraG head, int distance_from_root)
{
    pdijkstraG temp_dijkstra_node = head;
    while (temp_dijkstra_node != NULL)
    {
        if (temp_dijkstra_node->node->node_num == distance_from_root)
        {
            return temp_dijkstra_node;
        }

        temp_dijkstra_node = temp_dijkstra_node->next;
    }
    return NULL;
}

void freeList(pdijkstraG linked_list)
{
    while (linked_list != NULL)
    {
        pdijkstraG t = linked_list->next;
        free(linked_list);
        linked_list = t;
    }
    free(linked_list);
}

pdijkstraG min_dijkstra_node(pdijkstraG linked_list)
{
    int min = INFINITY;
    pdijkstraG min_node = NULL;
    while (linked_list != NULL)
    {
        if (linked_list->finish == 1)
        {
            linked_list = linked_list->next;
            continue;
        }
        if (linked_list->distance_from_root < min)
        {
            min_node = linked_list;
            min = linked_list->distance_from_root;
        }
        linked_list = linked_list->next;
    }
    if (min_node != NULL)
    {
        min_node->finish = 1;
    }
    return min_node;
}

void dijkstra(pdijkstraG my_list)
{
    pdijkstraG temp_dijkstra_node = min_dijkstra_node(my_list);
    while (temp_dijkstra_node != NULL)
    {
        pedge temp_edge = temp_dijkstra_node->node->edges;
        while (temp_edge != NULL)
        {
            pdijkstraG dest = get_dijkstra_node(my_list, temp_edge->endpoint->node_num);
            if (dest->distance_from_root > temp_dijkstra_node->distance_from_root + temp_edge->weight)
            {
                dest->distance_from_root = temp_dijkstra_node->distance_from_root + temp_edge->weight;
            }
            temp_edge = temp_edge->next;
        }
        temp_dijkstra_node = min_dijkstra_node(my_list);
    }
}

int shortsPath_cmd(pnode head, int src, int dest)
{
    pdijkstraG linked_list = init_dijkstra_graph(head, src);
    dijkstra(linked_list);
    pdijkstraG dest_node = get_dijkstra_node(linked_list, dest);
    int saved_distance = dest_node->distance_from_root;
    if (saved_distance == INFINITY)
    {
        freeList(linked_list);
        return -1;
    }
    freeList(linked_list);
    return saved_distance;
}

void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

int TSP_cmd(pnode *head)
{
    int list_length = 0;
    scanf("%d", &list_length);
    int *nodes_path = (int *)malloc(sizeof(int) * list_length);
    for (int i = 0; i < list_length; i++)
    {
        scanf("%d", &nodes_path[i]);
    }
    
    int final_distance = INFINITY;
    bool exist_final_path = false;

    for (int i = 0; i < list_length; i++)
    {
        for (int j = 0; j < list_length - 1; j++)
        {
            swap(&(nodes_path[j]), &(nodes_path[j + 1]));
            int path_length = 0;
            bool shortsPath_exist = true;
            for (int k = 0; k < list_length - 1; k++)
            {
                int distance = shortsPath_cmd(*head, *(nodes_path + k), *(nodes_path + (k + 1)));
                if (distance == -1)
                {
                    shortsPath_exist = false;
                    break;
                }
                path_length += distance;
            }
            if (path_length < final_distance && path_length != 0 && shortsPath_exist)
            {
                final_distance = path_length;
                exist_final_path = true;
            }
        }
    }
    free(nodes_path);
    if (!exist_final_path)
        return -1;

    return final_distance;
}

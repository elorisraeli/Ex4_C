#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
    int size = 0;
    scanf("%d", &size);
    char input = 'z';
    scanf("%c", &input);
    for (int i = 0; i < size; i++)
    {
        scanf("%c", &input);
        insert_node_cmd(head);
    }
}

void insert_node_cmd(pnode *head)
{
    int node_num = -1;
    scanf("%d", &node_num);
    pnode newNode = getNode(head, node_num);

    if (newNode == NULL)
    {
        newNode = (pnode)malloc(sizeof(node));
        newNode->node_num = node_num;
        newNode->edges = NULL;
        newNode->next = *head; // put newNode befor head
        *head = newNode;       // set newNode to be new head
    }
    else
    { // if node exist - delete all edges
        pedge tempEdge = newNode->edges;
        while (tempEdge != NULL)
        {
            pedge tempNext = tempEdge->next;
            free(tempEdge);
            tempEdge = tempNext;
        }
    }
    pedge *edgeNewNode = &(newNode->edges);
    int dest_node_num = -1;
    while (scanf("%d", &dest_node_num) != 0)
    {
        if (dest_node_num == 'n')
        {
            break;
        }
        pnode destNode = getNode(head, dest_node_num);
        if (destNode == NULL)
        { // if dont exists
            destNode = (pnode)malloc(sizeof(node));
            destNode->node_num = dest_node_num;
            destNode->edges = NULL;
            destNode->next = *head; // put him before the head
            *head = destNode;       // set him to be the new head
        }

        int edgeWeight = -1;
        scanf("%d", &edgeWeight);
        *edgeNewNode = (pedge)malloc(sizeof(edge));
        (*edgeNewNode)->endpoint = destNode;
        (*edgeNewNode)->weight = edgeWeight;
        (*edgeNewNode)->next = NULL;
        edgeNewNode = &((*edgeNewNode)->next);
    }
}

pnode getNode(pnode *head, int node_num)
{
    pnode tempNode = *head;
    while (tempNode != NULL)
    {
        if (tempNode->node_num == node_num)
        {
            return tempNode;
        }
        else
        {
            tempNode = tempNode->next;
        }
    }
    return NULL;
}

void deleteGraph_cmd(pnode *head)
{
    while ((*head) != NULL)
    {
        pedge tempEdge = (*head)->edges;
        while (tempEdge != NULL)
        {
            pedge tempNext = tempEdge->next;
            free(tempEdge);
            tempEdge = tempNext;
        }
        pnode tempNode = (*head);
        (*head) = (*head)->next;
        free(tempNode);
    }
    *head = NULL;
}

void free_edges(pnode nodeEdges)
{
    if (nodeEdges->edges != NULL)
    {
        pedge tempEdge = nodeEdges->edges;
        pedge tempNext;
        while (tempEdge != NULL)
        {
            tempNext = tempEdge;
            tempEdge = tempEdge->next;
            free(tempNext);
        }
    }
    else
    {
        free(nodeEdges->edges);
    }
}

void del_edge(pnode *head, int nodeId)
{
    pnode tempNode = *head;
    while (tempNode != NULL)
    {
        if (tempNode->node_num != nodeId && tempNode->edges != NULL)
        {
            if (tempNode->edges->endpoint->node_num != nodeId)
            {
                pedge tempEdge = tempNode->edges;

                while (tempEdge->next != NULL)
                {
                    if (tempEdge->next->endpoint->node_num == nodeId)
                    {
                        pedge p1 = tempEdge->next;
                        tempEdge->next = tempEdge->next->next;
                        free(p1);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else if (tempNode->edges->next == NULL)
            {
                pedge p1 = tempNode->edges;
                tempNode->edges = NULL;
                free(p1);
            }
            else
            {
                pedge p1 = tempNode->edges;
                tempNode->edges = p1->next;
                free(p1);
            }
        }
        tempNode = tempNode->next;
    }
}

void delete_node_cmd(pnode *head)
{
    int D = 0;
    scanf("%d", &D);
    del_edge(head, D);
    pnode tempNode = *head;
    node *p = NULL;
    if (tempNode->node_num != D)
    {
        while (tempNode->next->node_num != D)
        {
            tempNode = tempNode->next;
        }
        p = tempNode->next;
        tempNode->next = tempNode->next->next;
        free_edges(p);
        free(p);
    }
    else
    {
        p = *head;
        *head = p->next;
        free_edges(p);
        free(p);
    }
}
#include <stdlib.h>
#include <stdio.h>
#include "../Lista/lista.h"
#include <math.h>
#include "../Grafos/GrafoD.h"

typedef struct No{
    void* value;
    struct No *left;
    struct No *Right;
}Node;

typedef struct{
    void (*freeFunc)(void*);
    int (*compare)(void*, void*, int);
    int dimension;
    int size;
    Node *no;
}Tree;

void* KDT_create(int (*compare)(void*, void*, int), int dimension, void (*freeFunc)(void*)){
    Tree *result;
    result = (Tree*) calloc(1, sizeof(Tree));
    result->freeFunc = freeFunc;
    result->compare = compare;
    result->dimension = dimension;
    result->no = NULL;
    result->size = 0;
    return (void*) result;
}

void insert_Node(Node *n, Tree *tr, void* value, int dim){
    if(n->value == NULL){
        n->value = value;
        return;
    }

    if(dim == tr->dimension){
        dim = 0;
    }

    if(tr->compare(n->value, value, dim) < 0){
        if(n->left == NULL){
            n->left = (Node*) calloc(1, sizeof(Node));
            n->left->value=NULL;
            n->left->Right=NULL;
            n->left->left=NULL;
        }
        insert_Node(n->left, tr, value, dim+1);
        return;
    }else{
        if(n->Right == NULL){
            n->Right = (Node*) calloc(1, sizeof(Node));
            n->Right->value=NULL;
            n->Right->Right=NULL;
            n->Right->left=NULL;
        }
        insert_Node(n->Right, tr, value, dim+1);
        return;
    }
}


void KDT_insert(void* tree, void*value){
    Tree *tr;
    tr = (Tree*) tree;
    Node *n;
    n = (Node*) tr->no;
    if(n == NULL){
        n = (Node*) calloc(1, sizeof(Node));
        tr->no = n;
    } 
    insert_Node(n, tr, value, 0);
    tr->size+=1;
}

void freeNode(void* node, Tree* tr){
    Node *n;
    n = (Node*) node;
    if(n->left != NULL){
        freeNode(n->left, tr);
    }
    if(n->Right != NULL){
        freeNode(n->Right, tr);
    }
    tr->freeFunc(n->value);
    free(node);
}
void freeNodeSimple(void* node, Tree* tr){
    Node *n;
    n = (Node*) node;
    if(n->left != NULL){
        freeNodeSimple(n->left, tr);
    }
    if(n->Right != NULL){
        freeNodeSimple(n->Right, tr);
    }
    free(node);
}

void freeKDTree(void* tree){
    Tree *tr;
    tr = (Tree*) tree;
    if(tr->no != NULL)
    freeNode(tr->no, tr);
    tr->compare = NULL;
    tr->size=0;
    tr->dimension=0;
    free(tree);
}
void freeKDTreeSimple(void* tree){
    Tree *tr;
    tr = (Tree*) tree;
    if(tr->no != NULL)
    freeNodeSimple(tr->no, tr);
    tr->compare = NULL;
    tr->size=0;
    tr->dimension=0;
    free(tree);
}
Lista getAllNode(void* node, void* Lista){
    Node* no;
    no = (Node*) node;
    if(no == NULL){
        return Lista;
    }
    if(no->left != NULL){
       getAllNode(no->left, Lista);
    }
    if(no->value != NULL){
        Lista_insert(Lista, no->value);
    }
    if(no->Right != NULL){
        getAllNode(no->Right, Lista);
    }
    return Lista;   

}

Lista KDT_getAll(void* tree){
    Tree *tr;
    tr = (Tree*) tree;
    Lista * ls;
    ls = Lista_createLista();
    return getAllNode(tr->no, ls);
}

void* getValueNode(Tree* tree, Node* no, int dim, void* reference){
    if(no == NULL){
        return NULL;
    }
    if(dim == tree->dimension){
        dim = 0;
    }

    if(tree->compare(no->value, reference, dim) == 0 && tree->compare(no->value, reference, dim+1) == 0){
        return no->value;
    }
    if(tree->compare(no->value, reference, dim) < 0){
        return getValueNode(tree, no->left, dim, reference);
    }
    if(tree->compare(no->value, reference, dim) >= 0){
        return getValueNode(tree, no->Right, dim, reference);
    }

}

void* KDT_getValue(void* tree, void*reference){
    Tree * tr;
    tr = (Tree*) tree;
    int dim = 0;
    return getValueNode(tree, tr->no, dim, reference);
}

Lista removeValueNode(Tree* tree, Node* no, int dim, void* reference){
    if(no == NULL){
        return NULL;
    }
    if(no->value == NULL){
        return NULL;
    }
    if(dim == tree->dimension){
        dim = 0;
    }
    int i = tree->compare(no->value, reference, dim);
    Lista ls;
    if(i == 0 && tree->compare(no->value, reference, dim+1) == 0 ){
        ls = Lista_createLista();
        getAllNode(no->left, ls);
        getAllNode(no->Right, ls);
        no->value = NULL;
        no->left = NULL;
        no->Right = NULL;
        return ls;
    }

    if(i < 0){
        ls = removeValueNode(tree, no->left, dim+1, reference);
        if(ls == NULL){
            ls = removeValueNode(tree, no->Right, dim+1, reference);
        }
    }
    if(i >= 0){
        ls = removeValueNode(tree, no->Right, dim+1, reference);
        if(ls == NULL){
            ls = removeValueNode(tree, no->left, dim+1, reference);
        }
    }
    return ls;

}

void KDT_remove(void* tree, void*reference){
    Tree * tr;
    tr = (Tree*) tree;
    int dim = 0;
    Lista ls;
    ls = removeValueNode(tree, tr->no, dim, reference);
    if(ls == NULL){
        return;
    }
    void *t, *temp;
    t = Lista_getFirst(ls);
    while(1){
        temp = Lista_get(ls,t);
        if(temp){
            KDT_insert(tree, temp);
            t = Lista_getNext(ls, t);
        }else{
        break;
        }
    }   

}

double distKDT(Tree* tr, void* valueA, void* valueB){
    int i;
    double dist = 0;
    for(i = 0; i < tr->dimension; i++){
        dist = dist + pow(tr->compare(valueA, valueB, i),2);
    }
    return sqrt(dist);
}

void closestNeibordNode(Node *n, Tree* tr,void* reference ,void** item,double* dis, int dim){
    if(n == NULL || n->value == NULL)
    return;
    double distAtual = distKDT(tr, reference, n->value);
    if (distAtual < *dis && distAtual > 0){
        *dis = distAtual;
        *item = n->value;
    }
    if(tr->compare(n->value, reference, dim) < 0){
        closestNeibordNode(n->left, tr, reference, item, dis, dim+1);
        if(abs(tr->compare(n->value, reference, dim)) < *dis){
            closestNeibordNode(n->Right, tr, reference, item, dis, dim+1);
        }
    }else{
        closestNeibordNode(n->Right, tr, reference, item, dis, dim+1);
        if(abs(tr->compare(n->value, reference, dim)) < *dis){
            closestNeibordNode(n->left, tr, reference, item, dis, dim+1);
        }
    }

}

int KDT_Size(void* tree){
    Tree *tr;
    tr = (Tree*) tree;
    return tr->size;
}

void* closestNeibord(void* tree, void* reference){
    Tree *tr;
    tr = (Tree*) tree;
    Node *n;
    n = (Node*) tr->no;
    if(n == NULL){
        return NULL;
    } 
    void** item;
    item = (void**) calloc(1, sizeof(void*));
    *item = n->value;
    double *dis;
    dis = (double*) calloc(1, sizeof(double));
    *dis = distKDT(tr, reference, n->value);
    closestNeibordNode(n, tr, reference , item, dis, 0);
    return *item;
}

void itensInsideAreaNode(Tree* tr,Node* no,void* refInicial,void* refFinal,Lista ls, int dim){

    int compA, compB;
    if(no == NULL) return;
    //Comparadores, testar e verificar
    compA = tr->compare(refInicial, no->value, dim);
    compB = tr->compare(refFinal, no->value, dim);

    int control;
    control = compA * compB;
    if(control <= 0){
        itensInsideAreaNode(tr, no->left, refInicial, refFinal, ls, dim+1);
        itensInsideAreaNode(tr, no->Right, refInicial, refFinal, ls, dim+1);
        if(tr->compare(refInicial, no->value, dim+1) * tr->compare(no->value, refFinal, dim+1) <= 0){
            Lista_insert(ls, no->value);
        }
        return;
    }
    if(compA < 0){
        itensInsideAreaNode(tr, no->Right, refInicial, refFinal, ls, dim+1);
        return;
    }
    if(compB > 0){
        itensInsideAreaNode(tr, no->left, refInicial, refFinal, ls, dim+1);
        return;
    }

}

void* itensInsideArea(void* tree, void* refInicial, void* refFinal){
    Tree *tr;
    tr = (Tree*) tree;
    Lista ls = Lista_createLista();
    itensInsideAreaNode(tr, tr->no, refInicial, refFinal, ls, 0);
    return ls;
}

////////////////////////////////////////////////////////////////////////////

double pontos_dist(double x1, double x2, double y1, double y2){

    return  sqrt(pow(abs(x2 - x1),2)+pow(abs(y2 - y1),2));
}

void* getEsq(Node *no){
    if(no->left != NULL){
        return no->left->value;
    }else{
        return NULL;
    }
}

void* getDir(Node *no){
    if(no->Right != NULL){
        return no->Right->value;
    }else{
        return NULL;
    }
}

void* getValue(Node *no){
    return no->value;
}

void* getBranch(Node *no, int id){

    if(id==1){
        return no->left;
    }else{
        return no->Right;
    }

}

void* getNo(Tree *tree){
    return tree->no;
}

void closestEqualNeibordNode(Node *n, Tree* tr,void* reference ,void** item,double* dis, int dim){
    if(n == NULL)
    return;
    double distAtual = distKDT(tr, reference, n->value);
    if (distAtual < *dis){
        *dis = distAtual;
        *item = n->value;
    }
    if(tr->compare(n->value, reference, dim+1) < 0){
        closestNeibordNode(n->left, tr, reference, item, dis, dim+1);
        if(abs(tr->compare(n->value, reference, dim)) < *dis){
            closestNeibordNode(n->Right, tr, reference, item, dis, dim+1);
        }
    }else{
        closestNeibordNode(n->Right, tr, reference, item, dis, dim+1);
        if(abs(tr->compare(n->value, reference, dim)) < *dis){
            closestNeibordNode(n->left, tr, reference, item, dis, dim+1);
        }
    }

}

void* closestEqualNeibord(void* tree, void* reference){
    Tree *tr;
    tr = (Tree*) tree;
    Node *n;
    n = (Node*) tr->no;
    if(n == NULL){
        return NULL;
    } 
    void** item;
    item = (void**) calloc(1, sizeof(void*));
    *item = n->value;
    double *dis;
    dis = (double*) calloc(1, sizeof(double));
    *dis = distKDT(tr, reference, n->value);
    closestEqualNeibordNode(n, tr, reference , item, dis, 0);
    return *item;
}



void* closest(void* tree, void* reference){
    Tree* tr;
    tr = (Tree*) tree;
    Lista ls = KDT_getAll(tree);
    void* posic;
    posic = Lista_getFirst(ls);
    double dist;
    void* prox = Lista_get(ls, posic);
    dist = distKDT(tr, reference, prox);
    while(posic){
        void* atual = Lista_get(ls, posic);
        double distAtual = distKDT(tr, reference, atual);
        if(distAtual < dist){
            dist = distAtual;
            prox = atual;
        }
        posic = Lista_getNext(ls, posic);
    }
    return prox;

}
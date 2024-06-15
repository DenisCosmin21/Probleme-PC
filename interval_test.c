#include <stdio.h>
#include <stdlib.h>

typedef enum {show_max = 0, change = 1} operation;

struct nod
{
  int val;
  struct nod *left;
  struct nod *right;
  size_t max_interval;
  size_t min_interval;
};

typedef struct nod *  node;

int max(int a, int b)
{
  return a > b ? a : b;
}

node generate_tree(size_t left, size_t right, int *values)
{
  node tree = malloc(sizeof(struct nod));
  size_t mijl = (left + right) / 2;
  printf("%ld %ld %ld\n", left, right, mijl);
  if(left < right)
    {
      tree->min_interval = left;
      tree->max_interval = right;
      tree->left = generate_tree(left, mijl, values);
      tree->right = generate_tree(mijl + 1, right, values);
      tree->val = max(tree->left->val, tree->right->val);
    }
  else{
    printf("%ld %ld\n", left, right);
    printf("%ld\n", mijl);
    tree->val = values[mijl - 1];
    tree->min_interval = mijl;
    tree->max_interval = mijl;
    tree->left = NULL;
    tree->right = NULL;
  }
  return tree;
}

node initialize_tree(size_t min, size_t max, int *values)
{
  printf("%ld %ld\n", min, max);
  return generate_tree(min, max, values);
}

void show_node(node tree)
{
  printf("%ld:%ld\n =>", tree->min_interval, tree->max_interval);
  printf("%d\n", tree->val);
}

/*void parcurge_arbore(node tree, size_t left, size_t right)
{
  size_t mijl = (left + right) / 2;
  if(tree->left != NULL){
    parcurge_arbore(tree->left, left, mijl);
    // show_node(tree);
  }
  if(tree->right != NULL){
    parcurge_arbore(tree->right, mijl + 1, right);
  }
  show_node(tree);
}



node change_nodes(node tree, int position, int value, size_t left, size_t right)
{
  size_t mijl = (left + right) / 2;
  if(tree->left != NULL && tree->right != NULL){
    if(mijl < position){
      tree->right = change_nodes(tree->right, position, value, mijl+1, right);
      tree->val = max(tree->left->val, tree->right->val);
    }
    else{
      tree->left = change_nodes(tree->left, position, value, left, mijl);
      tree->val = max(tree->left->val, tree->right->val);
    }
  }
  else{
    tree->val = value;
  }
  return tree;
}
     
node change_tree(node tree, int *interval, int *values)
{
  values[interval[0] - 1] = values[interval[1] - 1];
  tree = change_nodes(tree, interval[0] - 1, values[interval[0] - 1], tree->min_interval, tree->max_interval);
  if(tree == NULL){
    printf("Err\n");
    exit(-1);
  }
  return tree;
}


*/

void parcurgere_afisare(node tree, size_t left, size_t right)
{
  size_t mijl = (left + right) / 2;
  if(tree != NULL){
    parcurgere_afisare(tree->left, left, mijl);
    parcurgere_afisare(tree->right, mijl + 1, right);
    show_node(tree);
  }
}

void show_tree(node tree)
{
  parcurgere_afisare(tree, tree->min_interval, tree->max_interval);
}

int check_interval(node tree, size_t left, size_t right, size_t *interval)
{
  size_t mijl = (left + right) / 2;
  //printf("%ld %ld %ld %ld %ld ", interval[0], interval[1], mijl, left, right);
  if(interval[0] == left && interval[1] == right){
    // printf("aici ");
    return tree->val;
    // printf("\n");
  }
  else{
    //printf("here ");
    if(interval[0] <= mijl && interval[1] > mijl){
      // printf("aici1 ");
      size_t aux;
      int val_l, val_r;
      aux = interval[1];
      interval[1] = mijl;
      //printf("varr : ");
      val_l = check_interval(tree->left, left, mijl, interval);
      interval[1] = aux;
      aux = interval[0];
      interval[0] = mijl + 1;
      // printf("%ld %ld %ld %ld %ld ", interval[0], interval[1], mijl, left, right);
      // printf("vall : ");
      val_r = check_interval(tree->right, mijl + 1, right, interval);
      interval[0] = aux;
      return max(val_l, val_r);
    }
    else if(interval[0] <= mijl && interval[1] <= mijl){
      //printf("aici2 ");
      return check_interval(tree->left, left, mijl, interval);
      //printf("\n");
    }
    else if(interval[0] > mijl && interval[1] > mijl){
      // printf("aici3 ");
      return check_interval(tree->right, mijl + 1, right, interval);
    }
    else{
      return tree->val;
    }
  }
}

node update_interval(node tree, size_t left, size_t right, size_t position, int value)
{
  size_t mijl = (left + right) / 2;
  if(tree->left != NULL && tree->right != NULL){
    if(position <= mijl){
      tree->left = update_interval(tree->left, left, mijl, position, value);
    }
    else{
      tree->right = update_interval(tree->right, mijl + 1, right, position, value);
    }
    tree->val = max(tree->left->val, tree->right->val);
  }
  else{
    tree->val = value;
  }
  return tree;
}
    
int get_maxim_interval(node tree, size_t *interval)
{
  return check_interval(tree, tree->min_interval, tree->max_interval, interval);
}

node change_tree(node tree, size_t *interval, int *values)
{
  values[interval[0] - 1] = interval[1];
  tree = update_interval(tree, tree->min_interval, tree->max_interval, interval[0], values[interval[0] - 1]);
  return tree;
}

int main(void)
{

  FILE *input = fopen("arbint.in", "r");
  FILE *output = fopen("arbint.out", "w");
  
  size_t N, M;
  int values[100000];
  operation op;
  int op_val;
  size_t op_interval[2];
  
  fscanf(input, "%ld", &N);
  printf("%ld", N);
  fscanf(input, "%ld", &M);

  for(size_t i = 0;i < N;i++){
    fscanf(input, "%d", &values[i]);
  }
  node tree = initialize_tree(1, N, values);
  //show_tree(tree);
  //printf("\n");
  while(M--){
    fscanf(input, "%d", &op_val);
    fscanf(input, "%ld", &op_interval[0]);
    fscanf(input, "%ld", &op_interval[1]);
    op = (operation)op_val;
    switch(op) {
    case show_max :
      fprintf(output, "%d\n", get_maxim_interval(tree, op_interval));
      //printf("%d\n", get_maxim_interval(tree, op_interval));
      //printf("new\n");
      break;
      case change:
      tree = change_tree(tree, op_interval, values);
      //show_tree(tree);
      break;
    default :
      break;
    }
  }
  
  fclose(input);
  fclose(output);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void show_stacks(Stack_t expression, Stack_t operatori)
{
  printf("st : ");
  show(operatori);
  printf("fp : ");
  show(expression);
}

void add_to_stack(Stack_t stack, char ch)
{
  push(stack, (Value_t){.value.ch = ch, .type = Char});
}

int8_t get_priority(int operator)
{
  if((operator == '(') || (operator == ')')){
    return 0;
  }
  else if((operator == '*') || (operator == '/')){
    return 1;
  }
  else if((operator == '+') || (operator == '-')){
    return 2;
  }
  else{
    return -1;
  }
}

bool bracket_end(Stack_t expression, Stack_t operatori)
{
  Value_t val;
  if(pop(operatori, &val) == true){
    while((return_value(val) != '(') && (size(operatori) > 0)){
      if(pop(operatori, &val) == false){
	printf("Error at pop operation");
	return false;
      }
      else{
	if(return_value(val) != '('){
	  push(expression, val);
	}
      }
    }
    if(size(operatori) <= 0 && return_value(val) != '('){
      printf("Error, no '(' sign");
      return false;
    }
    else{
      show_stacks(expression, operatori);
      return true;
    }
  }
  printf("Error, empty stack");
  return false;
}

bool priority_one(Stack_t expression, Stack_t operatori)
{
  Value_t val;
  if(size(operatori) > 0){
    if(peek(operatori, &val) == false){
      printf("Error, empty stack");
      return false;
    }
    if(get_priority(return_value(val)) == 1){
      push(expression, val);
      pop(operatori, NULL);
      show_stacks(expression, operatori);
    }
  }
  return true;
}

bool priority_two(Stack_t expression, Stack_t operatori)
{
  Stack_t operators_prior_two = init_stack(0);
  Value_t val = empty_val();
  bool change = false;
  while((size(operatori) > 0) && (return_value(val) != '(')){
    if(pop(operatori, &val) == false){
      destruct(operators_prior_two);
      printf("Eroare, stiva deja goala");
      return false;
    }
    if(get_priority(return_value(val)) == 1){
      push(expression, val);
      change = true;
    }
    else{
      push(operators_prior_two, val);
    }
  }
  while(size(operators_prior_two) > 0){
    pop(operators_prior_two, top_element(operatori));
  }
  if(change == true){
    show_stacks(expression, operatori);
  }
  destruct(operators_prior_two);
  return true;
}

bool sign_operation(Stack_t expression, Stack_t operatori)
{
  Value_t val;
  if(peek(operatori, &val) == false){
    printf("Empty stack");
    return false;
  }
  int8_t priority = get_priority(return_value(val));
  
  switch(priority){
  case 0:
    if(return_value(val) == ')'){
      return bracket_end(expression, operatori);
    }
    else{
      return true;
    }
    break;
  case 1:
    //return priority_one(expression, operatori);
    return true;
    break;
  case 2:
    return priority_two(expression, operatori);
    break;
  default:
    printf("Error, unknown operator");
    return false;
    break;
  }
}

bool parse_string(Stack_t expression)
{
  int c = 0;
  Stack_t operatori = init_stack(0);
  while(((c = getchar()) != EOF) && (c != '\n')){
    if(isalpha(c)){
      add_to_stack(expression, c);
      show_stacks(expression, operatori);
      if(priority_one(expression, operatori) == false){
	destruct(expression);
	destruct(operatori);
	return false;
      }
    }
    else{
      add_to_stack(operatori, c);
      show_stacks(expression, operatori);
      if(sign_operation(expression, operatori) == false){
	destruct(operatori);
	destruct(expression);
	return false;
      }
    }
   
  }
  if(size(expression) <= 0){
    printf("No input");
    destruct(operatori);
    destruct(expression);
    return false;
  }
  bool change = false;
  while(size(operatori) > 0){
    change = true;
    pop(operatori, top_element(expression));
  }
  if(change == true){
    show_stacks(expression, operatori);
  }
  destruct(operatori);
  return true;
}

int get_pos(char ch)
{
  return tolower(ch) - 'a';
}

bool read_input(int *values)
{
  int c = 0;
  int pos = 0;
  for(int i = 0;i < 28;i++){
      values[i] = 0;
  }
    while(((c = getchar()) != EOF) && (c != '0')){
      pos = get_pos(c);
      while(((c = getchar()) != EOF) && (c != '=')){
	continue;
      }
      if(c == EOF){
	printf("Wrong input");
	return false;
      }
      while(((c = getchar()) != EOF) && (!isdigit(c))){
	continue;
      }
      if(c == EOF){
	printf("Wrong input");
	return false;
      }
      values[pos] = c - '0';
      while(((c = getchar()) != EOF) && (c != '\n')){
	values[pos] *= 10;
	values[pos] += (c - '0');
      }
    }
    if(c == EOF){
      printf("Wrong input");
      return false;
    }
    return true;
}

int evaluate_calc(int a, int b, char ch)
{
  if(ch == '/'){
    if(b == 0){
      printf("\nCan't divide %d by 0\n", a);
      exit(1);
    }
  }
  switch(ch){
  case '*':
    return a * b;
  case '/':
    return a / b;
  case '+':
    return a + b;
  case '-':
    return a-b;
  default:
    return 0;
  }
}

int get_value(Value_t val, int *values)
{
  switch(val.type){
  case Char:
    return values[get_pos(return_value(val))];
    break;
  case Int:
    return return_value(val);
    break;
  default:
    return 0;
    break;
  }
}

int calculate_expression(Stack_t expression, int *values)
{
  Stack_t rez = init_stack(size(expression));
  Value_t val;
  Value_t val2;
  size_t i = 1;
  char op = 0;
  if(rotate_stack(expression) == false){
    printf("Wrong stack");
    exit(1);
  }
  else{
    while(size(expression) > 0){
      pop(expression, &val);
      if(isalpha(return_value(val))){
	push(rez, val);
      }
      else{
	op = return_value(val);
	printf("st : ");
	show(rez);
	printf("op : %c\n", op);
	pop(rez, &val);
	pop(rez, &val2);
	printf("r%ld : ", i); 
	show_elem(val2);
	printf(" %c ", op);
	show_elem(val);
	printf(" = %d\n", evaluate_calc(get_value(val2, values), get_value(val, values), op));
	printf("r%ld : %d %c %d = %d\n", i++, get_value(val2, values), op, get_value(val, values), evaluate_calc(get_value(val2, values), get_value(val, values), op));
	push(rez, (Value_t){.type = Int, .value.nr = evaluate_calc(get_value(val2, values), get_value(val, values), op)});
      }
    }
  }
  pop(rez, &val);
  int result = return_value(val);
  destruct(rez);
  return result;
}
	      
int parse_expression(Stack_t expression)
{
  int values[28];
  
  if(size(expression) <= 0){
    printf("Invalid stack");
    destruct(expression);
    exit(1);
  }
  else{
    if(read_input(values) == false){
      destruct(expression);
      exit(1);
    }
    else{
      return calculate_expression(expression, values);
    }
  }
}
	      
int main(void)
{
  uint8_t optiune = 0;
  Stack_t expression = init_stack(0);
  do{
    printf("Alegeti optiunea :\n1.Citire expresie in forma poloneza\n2.Calculare expresie\n3.Exit\n");
    if(scanf("%hhd", &optiune) != 1){
      break;
    }
    else{
      getchar();
      switch(optiune){
      case 1:
	if(size(expression) > 0){
	  destruct(expression);
	  expression = init_stack(0);
	}
	if(parse_string(expression) == false){
	  optiune = 3;
	}
	break;
      case 2:
	printf("Rezultatul expresiei este : %d\n", parse_expression(expression));
	break;
      default:
	destruct(expression);
	break;
      }
    }
  }while(optiune > 0 && optiune < 3);

  return 0;
}

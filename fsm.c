#include <stdio.h>

int countInputs(FILE *inputf){
  int lines=0;
  int ch=0;
  lines++;
  while(!feof(inputf))
    {
      ch = fgetc(inputf);
      if(ch == '\n')
	  lines++;
    }
  return lines;
}

int countTransitions(FILE *defs){
  int numTrans=0;
  int c=0;
  numTrans++;

  while(!feof(defs)) {
      c = fgetc(defs);
      if (c == '\n') {
	  if(numTrans > 50) {
	    printf("FSM can only take 50 states\n");
	  }
	  numTrans++;
      }  
  }
  return numTrans;
}
  
int main(int argc, char *argv[]){  
  FILE *inputf = fopen(argv[2], "r");     //argv[2]: input file
  int lines = countInputs(inputf);
  printf("this is how many lines are in the input file: %d\n", lines); //comment out later
  

  FILE *defs = fopen(argv[1], "r");       //argv[1]: fsm definition
  int trans = countTransitions(defs);
  printf("FSM has %d trans in the file \n", trans);
  fclose(defs);


  printf("processing FSM definition file %s\n", argv[1]);
  printf("processing FSM inputs file %s\n", argv[2]);
  //test to see if both files were able to be opened

  // Load data from FSM definition into 3 arrays:
  int currentStates[trans]; 
  char inputs[trans];
  int nextStates[trans];

  // Keeping track of what states we're on:
  int cur;
  char input;
  int next;

  int index = 0;
  int pattern;
  int pattern2;

  int step = 0; // how many steps we have done
  FILE *inp = fopen(argv[2], "r");       //argv[2]: inputs
  FILE *defin = fopen(argv[1], "r");      //argv[1]: fsm definition

  while ((pattern= fscanf(inp, "%c\n", &input)) != EOF) {
    while((pattern2 = fscanf(defin, "%d:%c>%d", &cur, &input, &next)) != EOF){
      currentStates[index]=cur;
      inputs[index]=input;
      nextStates[index]=next;
      index++;
      if (pattern && pattern2) {
	for (int i = 0; i <trans; i++) {
	  if (currentStates[i] == cur && inputs[i] == input) {
	    next = nextStates[i];
	    break;
	  }
	}
	printf("at step %d, input %c transitions FSM from state %d to state %d\n", step, input, cur, next);
	cur = next;
	step += 1;
      }
    }
  }
  fclose(inp);
  fclose(defin);
  printf("you did it AGAIN, avigail\n");
  printf("after %d steps, state machine finished successfully at state %d\n", step, cur);
}

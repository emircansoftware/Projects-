#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_HEALTH 100
#define MAX_STRENGTH 999

struct Soldier {
    int health;
    int strength;
};

struct Stack {
    struct Soldier soldiers[MAX_SIZE];
    int top;
};

void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

int isStackEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

int isStackFull(struct Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

void push(struct Stack* stack, struct Soldier soldier) {
    if (!isStackFull(stack)) {
        stack->soldiers[++stack->top] = soldier;
    } else {
        printf("Stack is full.\n");
    }
}

struct Soldier pop(struct Stack* stack) {
    if (!isStackEmpty(stack)) {
        return stack->soldiers[stack->top--];
    } else {
        
        struct Soldier emptySoldier = {0, 0};
        return emptySoldier;
    }
}

void fight(struct Stack* stack1, struct Stack* stack2) {
    struct Soldier soldier1 = pop(stack1);
    struct Soldier soldier2 = pop(stack2);
    
    
    int damage1 = (soldier1.strength - soldier2.strength) * (0.05) + 50;
    int damage2 = (soldier2.strength - soldier1.strength) * (0.05) + 50;
    
    soldier1.health -= damage2;
    soldier2.health -= damage1;
    printf("Soldier1's damage: %d\n", damage1);
    printf("Soldier2's damage: %d\n", damage2);
    
    
	
	if (soldier2.health <= 0) {
        printf("Side 2 soldier is dead.\n");
        soldier1.health+=damage2;
    } else {
        push(stack2, soldier2);
    }
	
	
    if (soldier1.health <= 0) {
        printf("Side 1 soldier is dead.\n");
    } else {
        push(stack1, soldier1);
    }
    
    

}

void RandomSoldier(struct Soldier* soldier) {
    soldier->health = rand() % (MAX_HEALTH + 1);
    soldier->strength = rand() % (MAX_STRENGTH + 1);
    printf("New soldier's health: %d  New soldier's strength:%d\n", soldier->health,soldier->strength);
}

int main() {
    srand(time(NULL));
    
    struct Stack side1, side2;
    initializeStack(&side1);
    initializeStack(&side2);
    
   
    
    while (true) {
    	
    	char game[1000];
        printf("Enter what you want:\n");
        fgets(game,1000,stdin);
        char *token = strtok(game, " ");
        char command = token[0];
        if(command == 'A'){
        	token = strtok(NULL, " ");
            int number = atoi(token);
            printf("add soldiers to side %d \n", number);
            token = strtok(NULL, ",");
                while (token != NULL) {
                    int health = atof(token);
                    token = strtok(NULL, ";");
                    int strength = atof(token);
                    printf("S - H:%d S:%d\n", health, strength);
                    struct Soldier newSoldier = {health, strength};
                    token = strtok(NULL, ",");

                    if (number == 1) {
                        push(&side1, newSoldier);
                    } else if (number == 2) {
                        push(&side2, newSoldier);
                    }

    
    
                }              

		}
		else if(command=='R'){
			int side;
            printf("Which side do you want to add random soldier\n");
            scanf("%d", &side);
            struct Soldier newSoldier;
            RandomSoldier(&newSoldier);
            if (side == 1) {
                push(&side1, newSoldier);
                
            } else if (side == 2) {
                push(&side2, newSoldier);
            }
		}
		else if(command=='F'){
			fight(&side1, &side2);
		}
		else if (command == 'C') {
            int side;
            printf("Which side do you want to remove soldier\n");
            scanf("%d", &side);
            struct Soldier newSoldier;
            if (side == 1) {
                pop(&side1);
                if(isStackEmpty(&side1)){
                	printf("Game Over");
                	exit(0);
				}
                
            } else if (side == 2) {
                pop(&side2);
                if(isStackEmpty(&side2)){
                	printf("Game Over");
                	exit(0);
				}
            }
        }
        else {
            printf("Invalid command.\n");
        }
        
        
        if( command=='F' ){
        if (isStackEmpty(&side1) || isStackEmpty(&side2) ){
        	printf("Game Over");
        	break;
		}
	 	
	}
	
        
        
        
    }
    
    return 0;
}

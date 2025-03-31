#include "interupt_handler.h"

#include <signal.h>
#include <stdlib.h>

unsigned char interupt_handler_interupted = 0;

interupt_handler_on_interupt_function* interupt_handler_on_interupt_functions;
unsigned int interupt_handler_on_interupt_functions_length;

void interupt_handler_initialize() {
  interupt_handler_on_interupt_functions = malloc(
    sizeof(interupt_handler_on_interupt_function) *
    interupt_handler_on_interupt_functions_length
  );

  struct sigaction signal_action;
  signal_action.sa_handler = interupt_handler_on_interupt;
  sigaction(SIGINT, &signal_action, (void*)0);
}

void interupt_handler_interupt_function_add(
  interupt_handler_on_interupt_function on_interupt_function
) {
  interupt_handler_on_interupt_functions_length = (
    interupt_handler_on_interupt_functions_length +
    1
  );

  interupt_handler_on_interupt_functions = realloc(
    interupt_handler_on_interupt_functions,
    sizeof(interupt_handler_on_interupt_function) * interupt_handler_on_interupt_functions_length
  );

  interupt_handler_on_interupt_functions[
    interupt_handler_on_interupt_functions_length -
    1
  ] = on_interupt_function;
}

void interupt_handler_interupt_function_remove(
  interupt_handler_on_interupt_function on_interupt_function
) {
  for (
    unsigned int interupt_handler_on_interupt_function_index = 0;
    interupt_handler_on_interupt_function_index < interupt_handler_on_interupt_functions_length;
    ++interupt_handler_on_interupt_function_index
  ) {
    if (
      interupt_handler_on_interupt_functions[
        interupt_handler_on_interupt_function_index
      ] == on_interupt_function
    ) {
      for (
        unsigned int interupt_handler_on_interupt_function_shift_index = interupt_handler_on_interupt_function_index;
        interupt_handler_on_interupt_function_shift_index < interupt_handler_on_interupt_functions_length - 1;
        ++interupt_handler_on_interupt_function_shift_index
      ) {
        interupt_handler_on_interupt_functions[
          interupt_handler_on_interupt_function_index
        ] = interupt_handler_on_interupt_functions[
          interupt_handler_on_interupt_function_index + 1
        ];
      }

      interupt_handler_on_interupt_functions_length = (
        interupt_handler_on_interupt_functions_length - 1
      );
      
      interupt_handler_on_interupt_functions = realloc(
        interupt_handler_on_interupt_functions,
        sizeof(interupt_handler_on_interupt_function) * interupt_handler_on_interupt_functions_length
      );
      
      interupt_handler_interupt_function_remove(on_interupt_function);

      break;
    }
  }
}

void interupt_handler_on_interupt(int interupt_code) {
  interupt_handler_interupted = interupt_code;

  for (
    unsigned int interupt_handler_on_interupt_function_index = 0;
    interupt_handler_on_interupt_function_index < interupt_handler_on_interupt_functions_length;
    ++interupt_handler_on_interupt_function_index
  ) {
    interupt_handler_on_interupt_functions[
      interupt_handler_on_interupt_function_index
    ](interupt_code);
  }
}


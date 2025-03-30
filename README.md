# interupt_handler

a_utility_library_for_catching_interupts

## usage

### initialization

```c
interupt_handler_initialize();
```

### callbacks

#### add

```c
interupt_handler_interupt_function_add(on_interupt_function);
```

#### remove

```c
interupt_handler_interupt_function_remove(on_interupt_function);
```

### status

```c
if (interupt_handler_interupted == 0) {
  // not_interupted_yet
} else {
  // has_been_interupted
  // `interupt_handler_interupted`:contains_interupt_code
}
```

## build

```sh
make
```

## clean

```sh
make clean
```

## copyright

> ©️ copyright:alic3dev[2025]|all_rights_reserved


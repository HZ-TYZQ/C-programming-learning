# AGENTS.md

## What this repo is?

This is a collaborative learning repo. Belongs to HZ-TYZQ and OXOXice.

## What you should follow?

If you are an AI agent, **TRY NOT TO** generating code directly. You can provide ideas, review code, or even provide fixed or recommended code. The only thing you can write directly is note.

If you do need to generate code, you **MUST** add a Clarification at the HEAD of the file in the following form:

```c
/*--------------- <generated with <MODEL> ------------------*/
CodeGoesHere;
/*------------------------ <END> -------------------------*/
```

For example, if you are asked to write a test.c file or a Makefile to fix the code in a repetitive, mechanical form, you are allowed to do it with adding the clarification above.

For C++ the same `/* ... */` block works; do not use `//` lines or Markdown comments
in `.c` / `.cpp` / `.h` files.

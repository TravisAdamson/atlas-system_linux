# Learning Objectives

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

## General

* What is a socket and how it is represented on a Linux/UNIX system
* What are the different types of sockets
* What are the different socket domains
* How to create a socket
* How to bind a socket to an address/port
* How to listen and accept incoming traffic
* How to connect to a remote application
* What is the the HTTP protocol
* How to create a simple HTTP server

# Requirements

## General

* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 20.04 LTS
* Your C programs and functions will be compiled with gcc 9.* using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* You are not allowed to have more than 5 functions per file
* All your header files should be include guarded
* Unless specified otherwise, you are allowed to use the C standard library

## More Info

* For the REST API part of this project, you can easily test your HTTP server, using curl, Postman, or even your browser …
* You are free to use any data structure that suits you as long as their purpose is well defined

## REST API
The goal of this project is to build a simple HTTP REST API in C.

This is going to be a really simple API, allowing us to manage a list of things to do (a.k.a a TODO list). Our database will be the RAM, meaning we won’t have any persistent storage. It’s not the purpose of this project anyway. Every time you start your server, the list of todos is empty.

A todo contains at least the following fields:

id -> Positive integer, starting from 0
title -> String
description -> String
Here are the different routes that will have to be implemented:

/todos
POST -> Creates a new todo
GET -> Retrieve all the todos
/todos?id={id} (where {id} is a positive integer)
GET -> Retrieve the todo with the corresponding id
DELETE -> Delete the todo with the corresponding id

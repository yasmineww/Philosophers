# Mandatory - Assignment

The purpose of this project is to learn how to handle multiple threads (inside a single process), trying to access shared resources. The goal is to make sure your code is optimized as much as possible by implementing thread synchronization, while avoiding all kind of conflicts (data races, deadlocks, leaks, undefined behaviors..). Of course, setting ridiculously long waiting times as a solution would be considered cheating, and cmon that’s definitely not smart so let’s be professionals here.

Our program will take a maximum of 5 arguments, the fifth being optional :

- number_of_philosophers (same as the number of forks)
- time_to_die (in milliseconds)
- time_to_eat (in milliseconds)
- time_to_sleep (in milliseconds)
- number_of_times_each_philosopher_must_eat (optional)

# Mandatory - key concepts

  At first, we must make sure to correctly parse our arguments, eliminating any characters other than numbers, and ensuring that the correct number of arguments was given. Next, we must understand few concepts related to threads and how they function:

## Threads and mutexes

  Threads are lightweight units of execution, that exist within a process. Our process can contain multiple threads that execute code independently, but still share memory and resources together. This unlocks more effecient communication, but require really careful management to avoid concurrency issues (eg. data races or deadlocks).

To solve this issue, we use **mutexes**. A **mutex** (short for “mutual exclusion”) is a synchronization primitive. It's essentially a lock and unlock mechanism that help regulate which and when a certain thread can access which resource and thus applying read and write operations without causing any data races. A **race condition** happen when more there is an attempt to perform two or more operations at the same time, resulting in undefined or unwated behaviors. Read more on data races **[here](https://www.techtarget.com/searchstorage/definition/race-condition)**. **Mutexes** are not like regular variables (e.g., integers) that hold values. It's an object or a structure that use **atomic operations** to lock and unlock itself. Atomic operations can never be interrupted until it's complete, which solves our problem avoiding any possible interruption that might cause multiple threads to gain access to critical sections of code simultaneously.

However, mutexes can often provoke **deadlocks**. It’s a situation in which each thread waits for a resource held by another thread, so it stays blocked forever waiting for the resource to be free (Often happens when the thread requires more than one resource to work). What happens is both threads lock their first mutexes exactly at the same time, in which case the program stays blocked because the threads are caught in a deadlock. A deadlock can also happen when a thread is waiting for a mutex that it already owns!

A deadlock can be solved by one of the following solutions:

1. Killing a thread or by redistributing resources.
2. Time intervals between resource requests have to be very long and far between.
3. Imposing a strict order for resource acquisition. The threads should both ask for `lock_1` first.
4. Forcing a thread to release a resource before asking for new ones, or before renewing its request.

# Mandatory - code

To start managing our flow of threads, we must first initialize our forks and other mutexes and assign each fork to its corresponding philosopher. We’ll have to initialize it with the  **pthread_mutex_init** function:

```
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
```

The state of the mutex becomes initialized and unlocked.

- **mutex**: a pointer to **pthread_mutex_t** type, pointing to **the mutex we want to initialize**.
- **mutexattr**: a pointer to specific attributes for the mutex. To use default attributes, we set it to **NULL**.

Assign left and right forks:

```
info->philo[i].r_fork = &info->forks[i];
info->philo[i].l_fork = &info->forks[(i + 1) % info->number_of_philosophers];
```

We will need to functions to lock and unlock our mutexes :

```
int pthread_mutex_lock(pthread_mutex_t *mutex));
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

Next we need to create our threads using the **pthread_create** function. It starts a new thread in the calling process. The thread will execute a specified function passsed as argument:

```
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
```

- **thread**: a pointer towards a **pthread_t** type variable, to store the ID of the thread we will be creating.
- **attr**: an argument that allows us to change the default attributes of the new thread(stack size, scheduling policy..). If NULL, the default attributes are set.
- **start_routine**: a function where the thread will start its execution. This function will have as its prototype: **void *function_name(void *arg);**.
- **arg**: a pointer towards an argument to pass to the thread’s `start_routine` function.

Now, we must create a **philosopher_routine** function. It’s a loop where each philosopher thinks, picks up its right and left forks, eats, puts down forks, and sleeps. 

When we no longer need a mutex, we should destroy it with the following **pthread_mutex_destroy** function:

```
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

This function checks if a mutex is unlocked and destroys the *unlocked* mutex, freeing whatever resources it might hold.

You might notice that I used the **pthread_detach** function, to correctly monitor my threads using the main process:

```
int pthread_detach(pthread_t thread);
```

It helped me to allow the main process to continue executing without the need to wait for each thread to finish (unlike **pthread_join**). Also, detach sets the program to automatically clean up the thread's resources after finishing execution.

# Bonus - Assignment

The bonus part revolves around the same core idea, n number of philosopher that must eat and avoid dying during the entire simulation. This time, we will be managing processes, not threads. Instead of assigning a left and right fork to each philosopher, we will have a bowl of forks (pool of resources) to be managed. Take note that the **main process is not a philosopher**. We will be exploring the concept of **semaphores**, instead of mutexes.

Our program will take the same input as the mandatory, and will be parsed similarly.

# Bonus - key concepts

## Processes and semaphores

When a program starts, it exists on the hard drive, the system loads the program's instructions into RAM. This state of execution in the RAM is a **process**. Processes run independently within separate virtual memory spaces, isolated and have complex communication.

We use fork() systemcall to create our philosophers (processes), which will be its exact clone and executed simultaneously. Each child process will have a distinct virtual memory but will still share the same RAM as the parent process. Also note that our philosophers will inherit the parent process instruction pointer which contains the memory address of the current instruction. So basically our philosophers will start executing code at the same place that the parent is. A child process doesn’t start all the way from the beginning of the code. 

In order to synchronize the resources that are still shared between processes, we use **semaphores**. A semaphore is a synchronization primitive, that answer to the same issue pointed out to by mutexes. The value of a semaphore represents the number of units available of the resource (number of forks available for use in the bowl). There exist a **binary** and a **counting** type of semaphore.

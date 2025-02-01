# ENEE447 2025 Spring Project 1: Prioritize Scheduling Task

## What are we doing in this project
- We will modify the scheduler in circle so that it implements priority scheduling.
	- Currently, the scheduler is a ["cooperative non-preemtive scheduler that uses the round-robin policy, without priorities"](https://github.com/sklaw/circle/blob/master/include/circle/sched/scheduler.h#L31-L33).
		- What is a cooperative non-preemtive scheduler? Read this wikipedia on [cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking).
	- We want to modify it so that it will prioritize scheduling tasks with highest priority.

## How to test your solution 
- **As an additional challenge in this project, you need to design a test for your implementation of priority scheduling.** (TAs will have some undisclosed tests for testing your code).
- Hint: The test can be developed based on the codes we already have in this sample. Specifically, you can modify the `Run` functions of [CScreenTask](screentask.cpp#L34-L51)/[CPrimeTask](primetask.cpp#L42-L84)/[CLEDTask](ledtask.cpp#L32-L47), then [create them in kernel.cpp with different priorities](kernel.cpp#L84-L94), then run the sample, then check the output to see whether those tasks are run from high priority to low priority.

### How to "run" a task?
- You may notice that every task defined here has a `Run` function, **does that mean we need to call a task's `Run` function ourselves to run the task? No.**
- Here is how a task starts running:
	- When we create an instance of a task, we will call `CTask`'s constructor because all tasks are subclasses of CTask. 
		- For example, [`CScreenTask` inherits `CTask` and thus is a subclass of `CTask`](screentask.h#L26).
	- [`CTask`'s constructor will call `InitializeRegs`](../../lib/sched/task.cpp#L48).
		- [`InitializeRegs` will initialize a task's `lr` register to point to `TaskEntry`](../..//lib/sched/task.cpp#L148).
			- **NOTE: This means when the scheduler schedules this task to run for the first time, the task will start running at `TaskEntry`.**
		- When scheduled to run, [`TaskEntry` will call the task's `Run` function](../..//lib/sched/task.cpp#L181).
			- Moreover, when the `Run` function returns, meaning the task is done, [`TaskEntry` will clean up the task by setting its state to `TaskStateTerminated` and yield to next task](../..//lib/sched/task.cpp#L183-L185).
	- [`Ctask`'s constructor will add the task to the scheduler](../..//lib/sched/task.cpp#L55) so that the task will be considered in future scheduling.

## How to test your code?

## Required Task


**How to build modified raspberry pi OS**
- kernel.img must be generated in the sample/43-ENEE447Project1 directory path.

```bash
# If you have modified source codes of the library (any code in lib or include)
./makeall clean && ./makeall

# If you have modified only codes in the sample but not in the library
cd sample/43-ENEE447Project1
make clean && make

```

**How to run on QEMU**
```bash
qemu-system-arm -M raspi0 -bios sample/43-ENEE447Project1/kernel.img
```



## Required Submission (Due Date : 3/2)

1. The file `scheduler.cpp` in which you have modified the function `GetNextTask`.
2. A pdf file, whicn includes the following:
	* Members of your group
	* Screenshot(s) of your QEMU output showing priority scheduling with a description of task priorities, and how you correctly implement. 
	* Describe your priority scheduling algorithm.


### Useful Link

* Understanding circle structure and functions provided in circle environment. 
	* circle-rpi documentation: https://circle-rpi.readthedocs.io/

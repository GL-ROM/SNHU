// Gabriel Romero
// Project One

package project_one;

import java.util.ArrayList;
import java.util.List;

public class TaskService {
	
	// Declaring list of tasks
	private List<Task> tasks;
	
	// Constructor For list
	public TaskService() {
		tasks = new ArrayList<Task>();
	}
	
	// Add to list
	public boolean add(Task task) {
		boolean alreadyPresent = false;
		for (Task t : tasks) {
			if (t.equals(task)) {
				alreadyPresent = true;
			}
		}
		if (!alreadyPresent) {
			tasks.add(task);
			return true;
		} else {
			throw new IllegalArgumentException("Invalid Task ID");
		}
	}
	
	// Call Task constructor
	public void addTask(String taskId, String taskName, String taskDescription) {
		Task task = new Task(taskId, taskName, taskDescription);
		this.add(task);
	}
	
	// Updaters for Name and Description
	public boolean updateTaskName(Task task, String name) {
		boolean change = false;
		for (Task t : tasks) {
			if (t.getTaskId().equals(task.getTaskId())) {
				task.setTaskName(name);
				change = true;
			}		
		}
		return change;
	}
	
	public boolean updateDescription(Task task, String name) {
		boolean change = false;
		for (Task t : tasks) {
			if (t.getTaskId().equals(task.getTaskId())) {
				task.setTaskDescription(name);
				change = true;
			}		
		}
		return change;
	}
	
	// Delete Task from list
	public boolean removeTask(Task task) {
		boolean removed = false;
		for (int i = 0; i < tasks.size(); i++) {
			if (tasks.get(i).getTaskId().equals(task.getTaskId())) {
				tasks.remove(task);
				removed = true;
			} else {
				removed = false;
			}
		}
		return removed;
	}

	public void printTasks() {
		System.out.println(tasks);
	}
}

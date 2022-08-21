// Gabriel Romero
// Project One

package project_one;

public class Task {
	// Fields
	private String taskId;
	private String taskName;
	private String taskDescription;
	
	// Task constructor
	public Task(String taskId, String taskName, String taskDescription) {
		if (taskId == null || taskId.length() > 10) {
			throw new IllegalArgumentException("Invalid Task ID");
		}
		
		this.taskId = taskId;
		
		if (taskName == null || taskName.length() > 20) {
			throw new IllegalArgumentException("Invalid Task Name");
		}
		
		this.taskName = taskName;
		
		if (taskDescription == null || taskDescription.length() > 50) {
			throw new IllegalArgumentException("Invalid Task Description");
		}
		
		this.taskDescription = taskDescription;
	}
	
	// Setters
	public void setTaskName(String name) {
		if (name == null || name.length() > 20) {
			throw new IllegalArgumentException("Invalid Task Name");
		} else {
			this.taskName = name;
		}
	}
	
	public void setTaskDescription(String description) {
		if (description == null || description.length() > 50) {
			throw new IllegalArgumentException("Invalid Task Description");
		} else {
			this.taskDescription = description;
		}
	}
	
	// Getters
	
	public String getTaskId() {
		return this.taskId;
	}
	
	public String getTaskName() {
		return this.taskName;
	}
	
	public String getTaskDescription() {
		return this.taskDescription;
	}
}

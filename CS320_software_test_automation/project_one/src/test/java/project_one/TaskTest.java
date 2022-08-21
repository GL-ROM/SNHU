// Gabriel Romero
// Project One


package project_one;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class TaskTest {

	@Test
	public void testTask() {
		Task task = new Task("1234567890", "Study", "Study For Exam");
		assertTrue(task.getTaskId().equals("1234567890"));
		assertTrue(task.getTaskName().equals("Study"));
		assertTrue(task.getTaskDescription().equals("Study For Exam"));
	}

	
	@Test
	public void testTaskIdIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task(null, "Study", "Study For Exam");
		}); 
	}
	
	@Test
	public void testTaskNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task("0987654321", null, "Study For Exam");
		}); 
	}
	
	@Test
	public void testTaskDescriptionIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task("0987654321", "Study", null);
		}); 
	}
	
	@Test
	public void testTaskIdTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task("0987654321415", "Study", "Study For Exam");
		}); 
	}
	
	@Test
	public void testTaskNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task("0987654321", "Study This Name is Too Long", "Study For Exam");
		}); 
	}
	
	@Test
	public void testTaskDescriptionTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Task("0987654321", "Study", "Study For Exam But this description is definitely too long");
		}); 
	}
	
	// Setters are tested within the Task Service That is why it is at 60%
}

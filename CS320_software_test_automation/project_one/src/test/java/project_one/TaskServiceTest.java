// Gabriel Romero
// Project One

package project_one;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class TaskServiceTest {

	@Test
	public void testTaskService() {
		TaskService ts = new TaskService();
		Task t1 = new Task("T0001","Study", "Study For Exam");
		Task t2 = new Task("T0002","Groceries", "Shop for the week");
		Task t3 = new Task("T0001","Bank", "Deposit Check");
		assertTrue(ts.add(t1));
		assertTrue(ts.add(t2));
		assertTrue(ts.add(t3));
	}
	
	@Test
	public void testUpdateTaskName() {
		TaskService ts = new TaskService();
		Task t1 = new Task("T0001","Study", "Study For Exam");
		ts.add(t1);
		ts.updateTaskName(t1, "Party");
		assertEquals("Party", t1.getTaskName());
	}
	
	@Test
	public void testUpdateTaskDescription() {
		TaskService ts = new TaskService();
		Task t1 = new Task("T0001","Study", "Study For Exam");
		ts.add(t1);
		ts.updateDescription(t1, "Party Time");
		assertEquals("Party Time", t1.getTaskDescription());
	}
	
	@Test 
	public void testTaskRemoval() {
		TaskService ts = new TaskService();
		Task t1 = new Task("T0001","Study", "Study For Exam");
		Task t2 = new Task("T0002","Groceries", "Shop for the week");
		Task t3 = new Task("T0003","Bank", "Deposit Check");
		assertTrue(ts.add(t1));
		assertTrue(ts.add(t2));
		assertTrue(ts.add(t3));
		
		// Test for task removal
		assertTrue(ts.removeTask(t3));
		assertTrue(ts.removeTask(t1));
		assertTrue(ts.removeTask(t2));
		
		// Test for task removed from table
		assertFalse(ts.removeTask(t3));
		assertFalse(ts.removeTask(t1));
		assertFalse(ts.removeTask(t2));

	}


	
}

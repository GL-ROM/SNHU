package project_one;

import static org.junit.jupiter.api.Assertions.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.junit.jupiter.api.Test;

class AppointmentServiceTest {
	
	@Test
	public void testAppointmentService() throws ParseException {
		
		String sDate1 = "2022-08-25";
		Date date1;
		date1 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate1);
		
		AppointmentService as = new AppointmentService();
		Appointment a1 = new Appointment("T0001", date1, "Ear Exam");
		Appointment a2 = new Appointment("T0002", date1, "Nose Exam");
		Appointment a3 = new Appointment("T0003 ", date1, "Eye Exam");
		assertTrue(as.add(a1));
		assertTrue(as.add(a2));
		assertTrue(as.add(a3));
	}
	
	@Test
	public void testAppointmentServiceStringInput() throws ParseException {
		
		AppointmentService as = new AppointmentService();
		assertTrue(as.addAppointment("T0001", "2022-09-25", "Ear Exam"));
		assertTrue(as.addAppointment("T0002", "2022-09-26", "Ear Exam"));
		assertTrue(as.addAppointment("T0003", "2022-09-27", "Ear Exam"));
	}

	@Test
	public void testAppointmentRemoval() throws ParseException {
		String sDate1 = "2022-08-25";
		Date date1;
		date1 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate1);
		
		AppointmentService as = new AppointmentService();
		Appointment a1 = new Appointment("T0001", date1, "Ear Exam");
		Appointment a2 = new Appointment("T0002", date1, "Nose Exam");
		Appointment a3 = new Appointment("T0003", date1, "Eye Exam");
		assertTrue(as.add(a1));
		assertTrue(as.add(a2));
		assertTrue(as.add(a3));
		
		// Test for Appointment removal
		assertTrue(as.removeAppointment(a3));
		assertTrue(as.removeAppointment(a1));
		assertTrue(as.removeAppointment(a2));
				
		// Test for Appointment removed from table
		assertFalse(as.removeAppointment(a3));
		assertFalse(as.removeAppointment(a1));
		assertFalse(as.removeAppointment(a2));
	}
}

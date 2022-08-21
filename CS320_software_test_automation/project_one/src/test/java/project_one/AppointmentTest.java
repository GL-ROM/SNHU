package project_one;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

class AppointmentTest {

	@Test
	public void testAppointment() throws ParseException {
		
		String sDate1 = "2022-08-15";
		
		Date date1;
	
		date1 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate1);
		
		// To pass as String for testing
		DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
		
		Appointment appointment = new Appointment("1234567890", date1, "Eye Exam");
		
		assertTrue(appointment.getAppointmentId().equals("1234567890"));
		assertTrue(dateFormat.format(appointment.getAppointmentDate()).equals("2022-08-15"));
		assertTrue(appointment.getAppointmentDescription().equals("Eye Exam"));
		
	}
	
	@Test
	public void testAppointmentDate() throws ParseException {
		String sDate2 = "2022-07-07";
		Date date2;
		date2 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate2);
		
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("0000000002", date2, "Eye Exam");
		}); 
	}
	
	@Test
	public void testAppointmentIdTooLong() throws ParseException {
		String sDate2 = "2022-08-09";
		Date date2;
		date2 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate2);
		
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("000000000200", date2, "Eye Exam");
		}); 
	}
	
	@Test
	public void testAppointmentDescriptionTooLong() throws ParseException {
		String sDate2 = "2022-08-10";
		Date date2;
		date2 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate2);
		
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("0000000002", date2, "Eye Exam that will take too long for you to get on your lunch break");
		}); 
	}
	
	@Test
	public void testAppointmentDateIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("0000000002", null, "Eye Exam");
		}); 
	}
	
	@Test
	public void testAppointmentIdIsNull() throws ParseException {
		String sDate2 = "2022-08-11";
		Date date2;
		date2 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate2);
		
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(null, date2, "Eye Exam");
		}); 
	}
	
	@Test
	public void testAppointmentDescriptionIsNull() throws ParseException {
		String sDate2 = "2022-09-07";
		Date date2;
		date2 = new SimpleDateFormat("yyyy-MM-dd").parse(sDate2);
		
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("0000000002", date2, null);
		}); 
	}
}

// Gabriel Romero
// Project One

package project_one;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class AppointmentService {

	// Declaring list of appointments
	private List<Appointment> appointments;
		
	// Constructor For list
	public AppointmentService() {
		appointments = new ArrayList<Appointment>();
	}
		
	// Add to list
	public boolean add(Appointment appointment) {
		boolean alreadyPresent = false;
		for (Appointment a : appointments) {
			if (a.equals(appointment)) {
				alreadyPresent = true;
			}
			if (a.getAppointmentId().equals(appointment.getAppointmentId()) ) {
				alreadyPresent = true;
			}
		}
		if (!alreadyPresent) {
			appointments.add(appointment);
			return true;
		} else {
			throw new IllegalArgumentException("Invalid Appointment ID");
		}
	}
		
	// String to Date Parse Method
	public Date StringToDate(String string){

		Date result = null;
		try{
			SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
		    result  = dateFormat.parse(string);
		}
		catch(ParseException e){
			throw new IllegalArgumentException("Invalid Date Format! Must be yyyy-MM-dd");
		}
	return result ;
	}
		
	// Call Appointment constructor
	public boolean addAppointment(String appointmentId, String stringAppointmentDate, String appointmentDescription) {
		Date appointmentDate = StringToDate(stringAppointmentDate);					// Convert String to Date
			
		// Pass proper variables to appointment constructor
		Appointment appointment = new Appointment(appointmentId, appointmentDate, appointmentDescription);
			
		// Call Add method to verify unique ID
		this.add(appointment);
		return true;
	}
		
	// Delete Appointment from list
	public boolean removeAppointment(Appointment appointment) {
		boolean removed = false;
		for (int i = 0; i < appointments.size(); i++) {
			if (appointments.get(i).getAppointmentId().equals(appointment.getAppointmentId())) {
				appointments.remove(appointment);
				removed = true;
			} else {
				removed = false;
			}
		}
		return removed;
	}
	
}

package com.example.project_three;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText username, password, repassword;
    Button signup, signin;
    DBHelper DB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Declaring variables that were created
        username    = (EditText) findViewById(R.id.username);
        password    = (EditText) findViewById(R.id.password);
        repassword  = (EditText) findViewById(R.id.repassword);
        signup      = (Button) findViewById(R.id.buttonsignup);
        signin      = (Button) findViewById((R.id.buttonsigin));
        DB          = new DBHelper(this);

        // Listeners
        signup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String user = username.getText().toString();
                String pass = password.getText().toString();
                String repass = repassword.getText().toString();

                if(user.equals("") || pass.equals("") || repass.equals(""))
                    Toast.makeText(MainActivity.this, "Please enter all fields", Toast.LENGTH_SHORT).show();
                else {
                    if(pass.equals(repass)) {
                        Boolean checkUser = DB.checkUsername(user);
                        if (checkUser == false) {
                            Boolean insert = DB.insertUser(user, pass);
                            if(insert == true) {
                                Toast.makeText(MainActivity.this, "Registration Successful", Toast.LENGTH_SHORT).show();
                                Intent intent = new Intent(getApplicationContext(), HomePage.class);
                                startActivity(intent);
                            } else {
                                Toast.makeText(MainActivity.this, "Registration Failed", Toast.LENGTH_SHORT).show();

                            }
                        } else {
                            Toast.makeText(MainActivity.this, "User Already Exists! Please Sign In.", Toast.LENGTH_SHORT).show();
                        }
                    } else {
                        Toast.makeText(MainActivity.this, "Passwords Do Not Match!", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

        signin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
                startActivity(intent);
            }
        });
    }
}
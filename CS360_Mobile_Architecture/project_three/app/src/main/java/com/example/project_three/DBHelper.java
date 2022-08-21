package com.example.project_three;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import androidx.annotation.Nullable;

import java.text.SimpleDateFormat;

public class DBHelper extends SQLiteOpenHelper {

    public static final String DBNAME = "ProjectThree.db";

    public DBHelper(Context context) {
        super(context, "ProjectThree.db", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase MyDB) {
        MyDB.execSQL("create Table users(username TEXT primary key, password TEXT)");
        MyDB.execSQL("create Table userData(date TEXT, weight REAL, user TEXT, FOREIGN KEY (user)" +
                     " REFERENCES users(username))");

    }

    @Override
    public void onUpgrade(SQLiteDatabase MyDB, int i, int i1) {
        MyDB.execSQL("drop Table if exists users");
        MyDB.execSQL("drop Table if exists userData");
    }

    public Boolean insertUser(String username, String password) {
        SQLiteDatabase MyDB         = this.getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        contentValues.put("username", username);
        contentValues.put("password", password);
        long result = MyDB.insert("users", null, contentValues);
        if (result == -1) return false;
        else
            return true;
    }

    public Boolean insertUserData(Float weight) {
        SQLiteDatabase MyDB         = this.getWritableDatabase();
        ContentValues contentValues = new ContentValues();
        SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd");
        contentValues.put("date", date.toString());
        contentValues.put("weight", weight);
        long result = MyDB.insert("users", null, contentValues);
        if (result == -1) return false;
        else
            return true;
    }

    public Boolean checkEntryDate() {
        SQLiteDatabase MyDB = this.getWritableDatabase();
        SimpleDateFormat date = new SimpleDateFormat("yyyy-MM-dd");
        Cursor cursor = MyDB.rawQuery("SELECT * FROM userData WHERE date = ?", new String[] {date.toString()});
        if (cursor.getCount() > 0)
            return true;
        else
            return false;
    }

    public Boolean checkUsername( String username ) {
        SQLiteDatabase MyDB = this.getWritableDatabase();
        Cursor cursor = MyDB.rawQuery("SELECT * FROM users WHERE username = ?", new String[] {username});
        if (cursor.getCount() > 0)
                return true;
            else
                return false;
    }

    public Boolean checkUsernamePassword(String username, String password) {
        SQLiteDatabase MyDB = this.getWritableDatabase();
        Cursor cursor = MyDB.rawQuery("SELECT * FROM users WHERE username = ? AND password = ?", new String[] {username, password});
        if (cursor.getCount() > 0)
            return true;
        else
            return false;
    }
}

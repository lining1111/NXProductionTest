package db

import (
	"fmt"
	"github.com/jmoiron/sqlx"
	_ "github.com/mattn/go-sqlite3"
)

type CL_ParkingArea struct {
	ID            int    `db:"ID"`
	Guid          string `db:"Guid"`
	ParkingAreaID string `db:"ParkingAreaID"`
	UName         string `db:"UName"`
	UPswd         string `db:"UPswd"`
	DBDataVersion string `db:"DBDataVersion"`
}

var ConfigDb *sqlx.DB
var IsOpen = false

func Open(path string) error {
	var err error
	ConfigDb, err = sqlx.Open("sqlite3", path)
	if err != nil {
		fmt.Printf("can not open db:%s,err:%v\n", path, err)
	}
	IsOpen = true
	return nil
}

func GetRowsFromTable_CL_ParkingArea() (CL_ParkingArea, error) {
	result := CL_ParkingArea{
		UName: "",
	}
	sqlCmd := "select * from  CL_ParkingArea"
	row := ConfigDb.QueryRowx(sqlCmd)
	if row.Err() != nil {
		return result, row.Err()
	}
	err := row.StructScan(&result)
	if err != nil {
		fmt.Printf(err.Error())
		return result, err
	}
	return result, nil
}

func GetUNameFromTable_CL_ParkingArea() (string, error) {
	var result = ""
	sqlCmd := "select UName from  CL_ParkingArea"
	row := ConfigDb.QueryRowx(sqlCmd)
	if row.Err() != nil {
		return result, row.Err()
	}

	err := row.Scan(&result)
	if err != nil {
		fmt.Printf(err.Error())
		return result, err
	}
	return result, nil
}

func SetUNameInTable_CL_ParkingArea(area *CL_ParkingArea) error {
	ConfigDb.Exec("delete from CL_ParkingArea")

	_, err := ConfigDb.Exec("replace into CL_ParkingArea("+
		"ID,"+
		"Guid,"+
		"ParkingAreaID,"+
		"UName,"+
		"UPswd,"+
		"DBDataVersion)"+
		"values(?,?,?,?,?,?)",
		area.ID,
		area.Guid,
		area.ParkingAreaID,
		area.UName,
		area.UPswd,
		area.DBDataVersion)
	return err
}

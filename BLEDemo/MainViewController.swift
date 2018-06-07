//
//  MainViewController.swift
//  CompassCompanion
//
//  Created by Rick Smith on 04/07/2016.
//  Copyright © 2016 Rick Smith. All rights reserved.
//

import UIKit
import CoreBluetooth

class MainViewController: UIViewController, CBCentralManagerDelegate, CBPeripheralDelegate {
    var manager:CBCentralManager? = nil
    var mainPeripheral:CBPeripheral? = nil
    var mainCharacteristic:CBCharacteristic? = nil
    
    let BLEService = "FFE0"
    let BLECharacteristic = "FFE1"
    
    var hour:Int = 0
    var minutes:Int = 0
    var seconds:Int = 0
    
    
    @IBOutlet weak var recievedMessageText: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        manager = CBCentralManager(delegate: self, queue: nil);
        
        customiseNavigationBar()
        
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: "dismissKeyboard")
        
        //Uncomment the line below if you want the tap not not interfere and cancel other interactions.
        //tap.cancelsTouchesInView = false
        
        view.addGestureRecognizer(tap)
        
    }
    
    func dismissKeyboard() {
        //Causes the view (or one of its embedded text fields) to resign the first responder status.
        view.endEditing(true)
    }
    
    func customiseNavigationBar () {
        
        self.navigationItem.rightBarButtonItem = nil
        
        let rightButton = UIButton()
        
        if (mainPeripheral == nil) {
            rightButton.setTitle("Scan", for: [])
            rightButton.setTitleColor(UIColor.blue, for: [])
            rightButton.frame = CGRect(origin: CGPoint(x: 0,y :0), size: CGSize(width: 60, height: 30))
            rightButton.addTarget(self, action: #selector(self.scanButtonPressed), for: .touchUpInside)
        } else {
            rightButton.setTitle("Disconnect", for: [])
            rightButton.setTitleColor(UIColor.blue, for: [])
            rightButton.frame = CGRect(origin: CGPoint(x: 0,y :0), size: CGSize(width: 100, height: 30))
            rightButton.addTarget(self, action: #selector(self.disconnectButtonPressed), for: .touchUpInside)
        }
        
        let rightBarButton = UIBarButtonItem()
        rightBarButton.customView = rightButton
        self.navigationItem.rightBarButtonItem = rightBarButton
        
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        if (segue.identifier == "scan-segue") {
            let scanController : ScanTableViewController = segue.destination as! ScanTableViewController
            
            //set the manager's delegate to the scan view so it can call relevant connection methods
            manager?.delegate = scanController
            scanController.manager = manager
            scanController.parentView = self
        }
        
    }
    
    // MARK: Button Methods
    @objc func scanButtonPressed() {
        performSegue(withIdentifier: "scan-segue", sender: nil)
    }
    
    @objc func disconnectButtonPressed() {
        //this will call didDisconnectPeripheral, but if any other apps are using the device it will not immediately disconnect
        manager?.cancelPeripheralConnection(mainPeripheral!)
    }
    
    @IBOutlet weak var numOfButton: UITextField!
    @IBOutlet weak var initButtonStat: UITextField!
    @IBOutlet weak var minuteSet: UITextField!
    @IBOutlet weak var secondSet: UITextField!
    
    @IBAction func alertSet(_ sender: Any) {
        
        //var numberInit:String? = nil
        var numberMinute:String = "00"
        var numberSecond:String = "00"
        
        
        if(minuteSet.text != nil){
        
            numberMinute = minuteSet.text!
            print(numberMinute)
            
        }
        if(secondSet.text != nil){
            numberSecond = secondSet.text!
            print(numberSecond)
        }
        
        
        
        var sendData : String = ""
        sendData.append("40000000000")
        
        
        if(numberMinute != ""){
        if(Int(numberMinute)!<10){
            sendData.append("0")
            sendData.append(numberMinute)
        }
        else {
            sendData.append(numberMinute)
        }
        }
        else {
            sendData.append("00")
        }
        
        
        if(numberSecond != ""){
            
        if(Int(numberSecond)!<10){
            sendData.append("0")
            sendData.append(numberSecond)
        }
        else {
        sendData.append(numberSecond)
        }
        }
        else {
            sendData.append("00")
        }
        sendData.append("1")

        
        
        print(sendData)
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        
        if (mainPeripheral != nil) {
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
    }
    
    @IBAction func alertSet1(_ sender: Any) {
        
        //var numberInit:String? = nil
        var numberMinute:String = "00"
        var numberSecond:String = "00"
        
        
        if(minuteSet.text != nil){
            
            numberMinute = minuteSet.text!
            
            
        }
        if(secondSet.text != nil){
            numberSecond = secondSet.text!
        }
        
        
        
        var sendData : String = ""
        sendData.append("40000000000")
        
        if(numberMinute != ""){
        if(Int(numberMinute)!<10){
            sendData.append("0")
            sendData.append(numberMinute)
        }
        else {
            sendData.append(numberMinute)
        }
        }
        else {
            sendData.append("00")
        }
        
        if(numberSecond != ""){
        if(Int(numberSecond)!<10){
            sendData.append("0")
            sendData.append(numberSecond)
        }
        else {
            sendData.append(numberSecond)
        }
        }
        sendData.append("0")
        
        print(sendData)
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        
        if (mainPeripheral != nil) {
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
    }
    
    
   
    
    
    @IBAction func sendButtonPressed(_ sender: AnyObject) {
        
        var numberInit:String? = nil
        
        if(numOfButton.text != nil){
             numberInit = numOfButton.text!
        
        }
        else if (numOfButton.text == nil) {
            numberInit = "3"
        }
        
        
        var initStat:String? = nil
        
        if(initButtonStat != nil){
            initStat = initButtonStat.text!
        }
        else if (numOfButton.text == nil){
            initStat = "0"
        }
        
        
        var sendData : String = "0"
        sendData.append(numberInit!)
        sendData.append(initStat!)
        
        print(sendData)
        
        //let helloWorld = "Hello World!"
        
        
//        let dataToSend = helloWorld.data(using: String.Encoding.utf8)
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        
        if (mainPeripheral != nil) {
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
    }
    
    @IBAction func mode2Init(_ sender: Any) {
        
        var numberInit:String? = nil
        
        if(numOfButton.text != nil){
            numberInit = numOfButton.text!
            
        }
        else {
            numberInit = "1"
        }
        
        
        var sendData:String = "1"
        sendData.append(numberInit!)
        
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func firstButtonOn(_ sender: Any) {
        
        let sendData:String = "11"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func firstButtonOff(_ sender: Any) {
        
        let sendData:String = "10"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func SecondButtonOff(_ sender: Any) {
        
        let sendData:String = "20"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func secondButtonOn(_ sender: Any) {
        
        let sendData:String = "21"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func ThirdButtonOff(_ sender: Any) {
        
        let sendData:String = "30"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    @IBAction func ThirdButtonOn(_ sender: Any) {
        
        
        let sendData:String = "31"
        
        let dataToSend = sendData.data(using: String.Encoding.utf8)
        if (mainPeripheral != nil) {
            
            mainPeripheral?.writeValue(dataToSend!, for: mainCharacteristic!, type: CBCharacteristicWriteType.withoutResponse)
        } else {
            print("haven't discovered device yet")
        }
        
    }
    
    
    
    
    
    
    // MARK: - CBCentralManagerDelegate Methods    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        mainPeripheral = nil
        customiseNavigationBar()
        print("Disconnected" + peripheral.name!)
    }
    
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print(central.state)
    }
    
    // MARK: CBPeripheralDelegate Methods
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        
        for service in peripheral.services! {
            
            print("Service found with UUID: " + service.uuid.uuidString)
            
            //device information service
            if (service.uuid.uuidString == "180A") {
                peripheral.discoverCharacteristics(nil, for: service)
            }
            
            //GAP (Generic Access Profile) for Device Name
            // This replaces the deprecated CBUUIDGenericAccessProfileString
            if (service.uuid.uuidString == "1800") {
                peripheral.discoverCharacteristics(nil, for: service)
            }
            
            //Bluno Service
            if (service.uuid.uuidString == BLEService) {
                peripheral.discoverCharacteristics(nil, for: service)
            }
            
            print(service.uuid.uuidString)
            
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {

        //get device name
        if (service.uuid.uuidString == "1800") {
            
            for characteristic in service.characteristics! {
                
                if (characteristic.uuid.uuidString == "2A00") {
                    peripheral.readValue(for: characteristic)
                    print("Found Device Name Characteristic")
                }
                
            }
            
        }
        
        if (service.uuid.uuidString == "180A") {
            
            for characteristic in service.characteristics! {
                
                if (characteristic.uuid.uuidString == "2A29") {
                    peripheral.readValue(for: characteristic)
                    print("Found a Device Manufacturer Name Characteristic")
                } else if (characteristic.uuid.uuidString == "2A23") {
                    peripheral.readValue(for: characteristic)
                    print("Found System ID")
                }
                
            }
            
        }
        
        if (service.uuid.uuidString == BLEService) {
            
            for characteristic in service.characteristics! {
                
                if (characteristic.uuid.uuidString == BLECharacteristic) {
                    //we'll save the reference, we need it to write data
                    mainCharacteristic = characteristic
                    
                    //Set Notify is useful to read incoming data async
                    peripheral.setNotifyValue(true, for: characteristic)
                    print("Found Bluno Data Characteristic")
                }
                
            }
            
        }
        
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        
        
        if (characteristic.uuid.uuidString == "2A00") {
            //value for device name recieved
            let deviceName = characteristic.value
            print(deviceName ?? "No Device Name")
        } else if (characteristic.uuid.uuidString == "2A29") {
            //value for manufacturer name recieved
            let manufacturerName = characteristic.value
            print(manufacturerName ?? "No Manufacturer Name")
        } else if (characteristic.uuid.uuidString == "2A23") {
            //value for system ID recieved
            let systemID = characteristic.value
            print(systemID ?? "No System ID")
        } else if (characteristic.uuid.uuidString == BLECharacteristic) {
            //data recieved
            if(characteristic.value != nil) {
                let stringValue = String(data: characteristic.value!, encoding: String.Encoding.utf8)!
            
                recievedMessageText.text = stringValue
            }
        }
        
        
    }
 
    
    
}





   
        //THIS IS WHERE YOU PASTE THE CODE TO CONNECT TO YOUR OWN DATABASE
        //Copy and paste the CDN bit of code from your app that you created on Firebase.
        //The script tag above is already there, so careful not to have duplicate script tags.
        //After you've copied and pasted, just delete the unnecessary script tags. 
        
        // alert("HI Firebase")
        import { initializeApp } from "https://www.gstatic.com/firebasejs/10.9.0/firebase-app.js";
        // (the one where you imported "initializeApp" from),
        //but change "firebase-app" to "firebase-database"
        
        const firebaseConfig = {
        apiKey: "AIzaSyCoC356_DOCykfHBgUHHKqtZKjP4PhtBoc",
        authDomain: "smartdoorlock-aec8c.firebaseapp.com",
        databaseURL: "https://smartdoorlock-aec8c-default-rtdb.asia-southeast1.firebasedatabase.app",
        projectId: "smartdoorlock-aec8c",
        storageBucket: "smartdoorlock-aec8c.appspot.com",
        messagingSenderId: "336953955441",
        appId: "1:336953955441:web:c4968f74b196dc7be4f7d0",
        measurementId: "G-0CK8WN3CB5"
        };

        import {getDatabase, ref, get, set, child, update, remove} from "https://www.gstatic.com/firebasejs/10.9.0/firebase-database.js"; //Copy and Paste the URL from near the top of the CDN you pasted in from firebase

        // Initialize Firebase
        const app = initializeApp(firebaseConfig);
        // const analytics = getAnalytics(app);
        const db = getDatabase();
        var toggleUnlock = document.querySelector("#toggleUnlock");
        var toggleLock = document.querySelector("#toggleLock");

        function Unlock() {
                
                update(ref(db, "Hotel/Room1/"),{
                    Door1 : 0
                })
                
                .then(()=>{
                })
                .catch((error)=>{
                    alert(error);
                });

        }
        function Lock() {
                
                update(ref(db, "Hotel/Room1/"),{
                    Door1 : 1
                })
                
                .then(()=>{

                })
                .catch((error)=>{
                    alert(error);
                });

        }

        toggleUnlock.addEventListener('click', Unlock);
        toggleLock.addEventListener('click', Lock);
        

        function dateInfo(){
            var checkIn = document.getElementById("checkIn");
            var checkOut = document.getElementById("checkOut");
            var Name = document.getElementById("Name");
            const dbRef = ref(getDatabase());
            get(child(dbRef, "Hotel/Room1/")).then((snapshot) => {
              if (snapshot.exists()) {
                Name.textContent = snapshot.val().Name;
                checkIn.textContent = "Check In : " + snapshot.val().CheckIn;
                checkOut.textContent = "Check Out : "  + snapshot.val().CheckOut;
          
              }
            }).catch((error) => {
                alert(error);
          });
                                   
          }
          window.onload = dateInfo();


          
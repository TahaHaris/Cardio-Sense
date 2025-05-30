// src/lib/firebaseconfig.js

// Import the functions you need from the Firebase SDKs
import { initializeApp } from 'firebase/app';
// Import the specific Firebase services you want to use
// Add any other services you plan to use, e.g., getAuth, getStorage
import { getFirestore } from 'firebase/firestore'; // For Cloud Firestore
import { getDatabase } from 'firebase/database';   // For Realtime Database (if you use it)
// import { getAuth } from 'firebase/auth';           // Uncomment if you need Authentication
// import { getStorage } from 'firebase/storage';       // Uncomment if you need Storage

const firebaseConfig = {
    apiKey: "AIzaSyD6ExgAAjOOfE2OLzpUd0ZLC0pQuV0iV_o",
    authDomain: "cardio-sense.firebaseapp.com",
    databaseURL: "https://cardio-sense-default-rtdb.firebaseio.com",
    projectId: "cardio-sense",
    storageBucket: "cardio-sense.firebasestorage.app",
    messagingSenderId: "410782322327",
    appId: "1:410782322327:web:b4a792873ce2243299a3d2"
  };

// Initialize Firebase
const app = initializeApp(firebaseConfig);

// Get a reference to the services you need and export them
// These are the instances you'll import into your components
export const db = getFirestore(app);           // For Cloud Firestore
export const rtdb = getDatabase(app);          // For Realtime Database
// export const auth = getAuth(app);              // Uncomment and export if you use Authentication
// export const storage = getStorage(app);        // Uncomment and export if you use Storage

// You can also export the app instance itself if needed
export default app;
#ifndef BASEMODEL
#define BASEMODEL

/*
 * Base class provides shared functionality to derived classes, reducing code repetition and improving maintenance.
 */
class BaseModel {
  public:  
    virtual String Type() {
      return "BaseModel";
    }

    // Name to describe the created instance
    String Name;
    // Hardcoded Globally Unique Identifier; used to identify each model type
    String ModelId;
    // Pretty Print name unique to each model
    String ModelName;

    /* Spare GUIDs, need more? https://guidgenerator.com/
      A91F0719-6863-416F-89F1-3A700F9AB4EF
      758A12B5-7BA3-4728-99DD-E485B1E84DF3
      13E2604A-D83B-401A-87CB-74B33F1AF885
      63E37A83-5678-4060-B46F-259C3A81DE89
      F33A7F17-04EC-4CB1-B9E5-1AC26C630198
      B5BA5590-3BC4-4778-82D0-E1486455E0CF
      14AA9A01-081F-4BAF-A305-047E3A66FAB3
      7607277B-B7A6-4F86-A980-E046F8409964
      BE4C6382-5569-469F-B940-143A6AD462C2
      09FCAE07-E4AE-46F9-B94E-9ECAD1C93803
      3FD63EB4-095C-4DF5-9777-A46B694DCBAE
      7F43E21A-453F-4513-B2A6-764301E0D166
      9FC57C40-E133-464E-9FA7-C3D707173000
      745798CA-2EB7-4386-9B63-2F5F2825540A
      1A49037F-CC51-4FA9-8F1C-7BB63B3FE1F2
      27A7CB9A-8398-4F8A-A1C6-A70FF611A062
      3A304120-1500-4C5F-9ADA-C332E4E4830A
    */

    // void println(String message, String messageType = "") {
    //   String prefix = "\n[" + Type() + "] ";
      
    //   int prefixLength = prefix.length();
    
    //   // Determine the number of spaces to add based on the length of the prefix
    //   int spacesToAdd = 30 - prefixLength;
    
    //   // Add the required number of spaces to the end of the prefix
    //   for (int i = 0; i < spacesToAdd; i++) {
    //     prefix += " ";
    //   }

    //   // Add optional marker based on type
    //   if (messageType == "error") // Use for critically breaking things
    //   {
    //     message = "✖ " + message;
    //   }
    //   else if (messageType == "warning") // Use for non-critical breaking things, but should not be this way
    //   {
    //     message = "⚠ " + message;
    //   }
    //   else if(messageType == "todo") // Use to include to-do's in the logs
    //   {
    //     message = "⚑ " + message;
    //   }
    //   else if(messageType == "configure") // Use for code that configures things to make them easier to spot
    //   {
    //     message = "⚙ " + message;
    //   }
    //   else // add empty spaces so messages align
    //   {
    //     message = "  " + message;
    //   }
    
    //   Serial.print(prefix + message);
    // }

    // // A passthrough of the regular print method (to allow for easier to read code)
    // void print(String message) {
    //   Serial.print(message);
    // }
};
#endif

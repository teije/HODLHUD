/* TODO 

[ ] We want to: Consistently log code results/status during operation
    [ ] For this we need to: Create Logger class
        And that requires the following:
        [ ] Create properties
            [ ] Name:        string
            [ ] Shape Type:  string     
            [ ] Start Pos X: int 
            [ ] Start Pos Y: int
            [ ] Width (X):   int
            [ ] Width (Y):   int
        [ ] Create functions
            [ ]   
    [ ] Call upon logger class from each other class

[ ] We want to: Connect to WiFi
    [ ] Create WiFi connector class
        [ ] Create properties
            [ ] SSID:     string
            [ ] Password: string
        [ ] Create functions
            [ ] Connect()     return boolean:connectionSuccesful
            [ ] Reconnect()   return boolean:connectionSuccesful
            [ ] IsConnected() return boolean:isConnected
        [ ] Initialize WiFi connector class
        [ ] Establish a WiFi connection
        [ ] Allow the connection/testing multiple WiFi connections
        
[ ] We want to: Fetch and store data (from the Binance API)
    [ ] Create a class to hold currency data
        [ ] Create a CurrencyPair class/object 
            [ ] Create properties
                [ ] Main Currency:    string     
                [ ] Cointer Currency: string
                [ ] Spot Price:       float
            [ ] Create functions
                [ ]     
            
    [ ] Make an API call to Binance
        [ ] Create Binance API service class
            [ ] Create properties
                [ ] Name:     string
                [ ] Base URL: string
                [ ] API Key:  string
            [ ] Create functions
                [ ] getWalletContents()                           return JSON string
                [ ] getSpotPrice(dateTime=default:now)            return JSON string
                [ ] getPriceForPeriod(startDateTime, endDateTime) return JSON string
                [ ]

[ ] We want to: Print visual elements to the display
    [ ] Create a UIElement data object
        [ ] Create properties
            [ ] Name:         string
            [ ] Shape Type:   string     
            [ ] Start Pos X:  int 
            [ ] Start Pos Y:  int
            [ ] Width (X):    int
            [ ] Width (Y):    int
            [ ] Colour/Shade: int/string
        [ ] Create functions
            [ ]     
    
    [ ] Create a Display printer class (that prints UIElements)
        [ ] Create properties
                [ ]  
            [ ] Create functions
                [ ] DisplayElement(UIElement)
                [ ] Reset Display Fully()
                [ ] Reset Display Partially()
                [ ] 

    
*/
void setup() {

}

void loop() {

}

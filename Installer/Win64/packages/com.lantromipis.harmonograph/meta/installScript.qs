function Component()
{
    // default constructor
}
Component.prototype.createOperations = function()
{
    try {
        component.createOperations();
        if (installer.value("os") == "win") { 
            try {
                var userProfile = installer.environmentVariable("USERPROFILE");
                installer.setValue("UserProfile", userProfile);
                component.addOperation("CreateShortcut", "@TargetDir@\\Harmonograph.exe", "@UserProfile@\\Desktop\\Harmonograph.lnk");
            } catch (e) {
                // Do nothing if key doesn't exist
            }
        }
    } catch (e) {
        print(e);
    }
}
#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Simulate a failure for temperatures above a certain threshold
    // Return 200 for ok
    // Return 500 for not-ok
    if (celcius > 200) {
        return 500;  // Simulate failure for high temperatures
    }
    return 200;  // Simulate success for normal temperatures
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // Increment the failure count on non-ok response
        alertFailureCount += 1;
    }
}

int main() {
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    assert(alertFailureCount == 1);  // Test to ensure failure count is accurate
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}

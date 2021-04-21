float roundFloat(float var) {
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =3767.16    for rounding off value
    // then type cast to int so value is 3767
    // then divided by 100 so the value converted into 37.67
    float value = (int)(var * 100 + 0.5);
    return (float)value / 100;
}

float getAverage(float array[]) {
    float average = 0;
    int zerosFound = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        average += array[i];
        if (array[i] == 0.0) {
            zerosFound++;
        } 
        #if DEBUG_LEVEL >= 5
            Serial.print(array[i]);
            Serial.print(" ");
        #endif
    }
    int nonZeroValues = ARRAY_SIZE - zerosFound;
    average /= nonZeroValues;
    average = roundFloat(average);
    #if DEBUG_LEVEL >= 5
        Serial.print("Average of array: ");
        Serial.println(average);
    #endif

    return average;
}
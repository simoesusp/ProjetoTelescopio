// Programa que converte entre Right Ascension e Hora Angle

// Boa explicacao: http://www.princeton.edu/~achaney/tmve/wiki100k/docs/Hour_angle.html
//                  http://books.google.com.br/books?id=DwJfCtzaVvYC&pg=PA35&lpg=PA35&dq=convert+ra+to+hour+angle&source=bl&ots=93j6VKdAsJ&sig=kyMMZ4EwDE7ph3C0IcxWHceRIP4&hl=en&sa=X&ei=vKpJVKLoBcrBggTwu4GYBg&ved=0CD0Q6AEwBA#v=onepage&q=convert%20ra%20to%20hour%20angle&f=false

// Local Time to Sidereal Time Converter: http://www.conspiracyoflight.com/sidereal/localsiderealconverter.htm
//     Tambem calcula UT, JD !!

// Outro Conversor: http://aa.usno.navy.mil/data/docs/JulianDate.php

// Julian Day: http://en.wikipedia.org/wiki/Julian_day

int main()
{

//    double UT = currentTime.time().hour() + (currentTime.time().minute() / 60.0) + (currentTime.time().second() / 3600.0) + (currentTime.time().msec() / 3600000.0);

    double hour = 13;
    double minute = 55;
    double second = 50;
    double Fuso = 3;

    double UT = hour + (minute / 60.0) + (second / 3600.0) + Fuso;
    printf("UT: %f\n" , UT);

    double JD0 = 2456955.12211;  // Peguei direto do F5 do Stelarium !!

    double JD = 2456954.5;    // 2456955.12211 //2444351.5;
            // http://www.conspiracyoflight.com/sidereal/localsiderealconverter.htm

    double RAH = 12;
    double RAM = 27;
    double RAS = 26;
    double RA  = (RAH+RAM/60.0+RAS/3600.0);

/*    double LATH = 22;
    double LATM = 1;
    double LAT = -1*(LATH+LATM/60.0); // -1 sul

    double LONGH = 47;
    double LONGM = 53;
    double LONG = -1*(LONGH+LONGM/60.0);// -1 west
*/
    double LONGH = 47;
    double LONGM = 53;
    double LONGDegrees = -1*(LONGH+LONGM/60.0);// -1 west

    printf("LongDegrees: %f\n" , LONGDegrees);

        // O link pra esse metodo ta' com o Lucas!
    double decimalHours = UT;
    double daysFromJ2000 = JD0 - 2451545.0;
    //double LST = 100.46 + (0.985647 * daysFromJ2000) + LONG + (15 * decimalHours);
    double LSTDegrees = 100.46 + (0.985647 * daysFromJ2000) + LONGDegrees + (15 * decimalHours);

    while (LSTDegrees < 0) {
        LSTDegrees += 360.0;
    }
    while (LSTDegrees > 360) {
        LSTDegrees -= 360.0;
    }

    printf("LSTDegrees: %f\n", LSTDegrees);

    double RADegrees = RA * 15.0;
    printf("RA: %f      RADegrees: %f\n", RA, RADegrees);

    double HADegrees = LSTDegrees - RADegrees;
    while (HADegrees < 0) {
        HADegrees += 360.0;
    }
    while (HADegrees > 360) {
        HADegrees -= 360.0;
    }

    printf("HADegrees: %f\n", HADegrees);
    double HA = HADegrees / 15.0;

    int HAh, HAm, HAs;
    HAh = (int) HA;
    HAm = (int) ((HA - HAh)*60);
    HAs = (int) ((((HA - HAh)*60) - HAm)*60);

    printf("HAh = %d   HAm = %d    HAs = %d\n\n\n", HAh, HAm, HAs);


            // Origem das seguintes equacoes: https://sites.google.com/site/physics135/Home/announcements/universaltimetolocalsiderealtimeconversion
    double GMST_hours = 6.656306 + 0.0657098242*(JD-2445700.5) + 1.0027379093*UT;
    printf("GMST_hours: %f           ", GMST_hours);

    double LST_hours = GMST_hours + (LONGDegrees/15.0);
    while (GMST_hours < 0) {
        GMST_hours += 24.0;
    }
    while (GMST_hours > 24) {
        GMST_hours -= 24.0;
    }
    printf("GMST_hours: %f\n", GMST_hours);

    while (LST_hours < 0) {
        LST_hours += 24.0;
    }
    while (LST_hours > 24) {
        LST_hours -= 24.0;
    }
    printf("LST_hours: %f\n", LST_hours);

            // Proximas equacoes: http://en.wikipedia.org/wiki/Hour_angle
    HA = LST_hours - RA;
    while (HA < 0) {
        HA += 24.0;
    }
    while (HA > 24) {
        HA -= 24.0;
    }

    printf("HA: %f\n", HA);


    HAh = (int) HA;
    HAm = (int) ((HA - HAh)*60);
    HAs = (int) ((((HA - HAh)*60) - HAm)*60);


    printf("HAh = %d   HAm = %d    HAs = %d\n\n\n", HAh, HAm, HAs);


    // Essa ultima abaixo NAO FUNCIONOU!!!!
        // http://en.wikipedia.org/wiki/Sidereal_time
    GMST_hours = 18.697374558 + 24.06570982441908 * daysFromJ2000;

    printf("GMST_hours: %f           ", GMST_hours);

    LST_hours = GMST_hours + (LONGDegrees/15.0);
    while (GMST_hours < 0) {
        GMST_hours += 24.0;
    }
    while (GMST_hours > 24) {
        GMST_hours -= 24.0;
    }
    printf("GMST_hours: %f\n", GMST_hours);


	return 0;
}




# I2CServo-Check
gather all Servo limits for SpiderRoy

# Anleitung
Sobald die Hardware steht müssen noch die "Aktionsbereiche" der Servos eingestellt werden.

Diese sind meist für jedes Bein unterschiedlich, nur in wenigen Fällen ist genug Platz um den kompletten Bereich eines Servos anzufahren ohne dass sich die Beine gegenseitig ins Gehege kommen.

Auch ist es nicht einfach die Verkabelung der Servos fehlerfrei nach Schema zu machen (es sind immerhin 20 Servos inkl. Kopf).
Um hier die Arbeit zu erleichtern habe ich dieses kleine Programm geschrieben.

Das Programm fragt nacheinander für jeden Port der I²C Servo Treiber Minimum, Maximum und Nummer des Servos nach Schema ab.
Zum Einstellen des Minimum und Maximum wird jeweis die Eingabe von "+" und "-" erwartet und der Servo entsprechend um einen Tick vor oder zurückgefahren.

Absolutes Minimum ist 5 Maximum ist 27.

Zu beachten ist, dass Mimimum bedeutet, dass das Bein ganz nach hinten unten bzw zum Körper hin bewegt wird, es also immer wieder vorkommt, dass das Minimum größer als das Maximum ist.

Ist die Position erreicht muss der Wert mit "x" bestätigt werden.

Sind Minimum und Maximum erfasst erfolgt die Abfrage der Servo-Nummer nach ServoPosition.png.

Nach Abfrage aller 2x16 PWM-Ports wird das Ergebnis auf Bildschirm und in die Datei I2CServos.txt ausgegeben.

Der Inhalt der Datei läßt sich direkt in den Code von SpiderRoy an die entsprechende Stelle einfügen.

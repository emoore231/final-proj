 for ($i = 0; $i -lt 30; $i++)
{
adb -s ZY22DR94GQ shell input tap 300 120
start-sleep -milliseconds 250
adb -s ZY22DR94GQ shell input tap 560 120
start-sleep -milliseconds 250
adb -s ZY22DR94GQ shell input text ("'" + (get-random -inputobject $queries) + "'")
start-sleep -milliseconds 250
adb -s ZY22DR94GQ shell input keyevent 66
start-sleep -milliseconds 2500
}
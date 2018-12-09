// World datetime
void WorldDateTime(int year, int month, int day, int hour, int minutes) {
	GetGame().GetWorld().SetDate(year, month, day, hour, minutes);
}
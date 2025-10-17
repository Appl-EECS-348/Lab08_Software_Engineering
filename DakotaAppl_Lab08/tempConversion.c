/* Temperature conversion utility
 * Prompts user for a temperature value, original scale (C/F/K), and target scale (C/F/K).
 * Converts the temperature, prints the converted value, categorizes it based on Celsius ranges,
 * and provides a simple weather advisory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double to_celsius(double value, char scale, int *ok) {
	*ok = 1;
	if (scale == 'C') return value;
	if (scale == 'F') return (value - 32.0) * 5.0 / 9.0;
	if (scale == 'K') return value - 273.15;
	*ok = 0; return 0.0;
}

double from_celsius(double c, char scale, int *ok) {
	*ok = 1;
	if (scale == 'C') return c;
	if (scale == 'F') return c * 9.0 / 5.0 + 32.0;
	if (scale == 'K') return c + 273.15;
	*ok = 0; return 0.0;
}

const char *category_and_advisory(double celsius, char *category_out, char **advisory_out) {
	if (celsius < 0.0) {
		*category_out = 'F'; // Freezing
		*advisory_out = "Wear a heavy coat!";
		return "Freezing";
	}
	if (celsius >= 0.0 && celsius < 10.0) {
		*category_out = 'C'; // Cold
		*advisory_out = "Wear a jacket.";
		return "Cold";
	}
	if (celsius >= 10.0 && celsius < 25.0) {
		*category_out = 'O'; // Comfortable
		*advisory_out = "Comfortable — no special precautions.";
		return "Comfortable";
	}
	if (celsius >= 25.0 && celsius < 35.0) {
		*category_out = 'H'; // Hot
		*advisory_out = "Drink lots of water!";
		return "Hot";
	}
	// celsius >= 35
	*category_out = 'E';
	*advisory_out = "Extreme heat — stay indoors and avoid strenuous activity.";
	return "Extreme Heat";
}

int main(void) {
	char buf[128];
	double value;
	char in_scale, out_scale;

	// Read temperature value
	printf("Enter the temperature value: ");
	if (fgets(buf, sizeof buf, stdin) == NULL) return 0;
	char *endptr;
	value = strtod(buf, &endptr);
	if (endptr == buf) {
		printf("Invalid temperature value.\n");
		return 1;
	}

	// Read original scale
	printf("Enter the original scale (C, F, or K): ");
	if (fgets(buf, sizeof buf, stdin) == NULL) return 0;
	// find first non-space character
	int i = 0; while (buf[i] && isspace((unsigned char)buf[i])) ++i;
	if (!buf[i]) { printf("Invalid scale.\n"); return 1; }
	in_scale = toupper((unsigned char)buf[i]);

	// Read target scale
	printf("Enter the scale to convert to (C, F, or K): ");
	if (fgets(buf, sizeof buf, stdin) == NULL) return 0;
	i = 0; while (buf[i] && isspace((unsigned char)buf[i])) ++i;
	if (!buf[i]) { printf("Invalid scale.\n"); return 1; }
	out_scale = toupper((unsigned char)buf[i]);

	int ok;
	double c = to_celsius(value, in_scale, &ok);
	if (!ok) {
		printf("Invalid input scale '%c'. Use C, F, or K.\n", in_scale);
		return 1;
	}

	double converted = from_celsius(c, out_scale, &ok);
	if (!ok) {
		printf("Invalid output scale '%c'. Use C, F, or K.\n", out_scale);
		return 1;
	}

	// Print converted value with two decimal places
	printf("Converted temperature: %.2f %c\n", converted, out_scale);

	char cat_char = 0;
	char *advisory = NULL;
	const char *category = category_and_advisory(c, &cat_char, &advisory);
	printf("Temperature category: %s\n", category);
	printf("Weather advisory: %s\n", advisory);

	return 0;
}
// ============================================================================
// CST-AI: Cosine, Sine, Tangent - Advanced Implementation
// ============================================================================
// This is an enhanced example demonstrating trigonometric function analysis
// with iterative refinement techniques based on the original CST algorithm.
// ============================================================================

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// ============================================================================
// Helper Function: Print formatted headers for output
// ============================================================================
void printHeader() {
    cout << "\n========== CST-AI: Trigonometric Analysis ==========\n";
    cout << setw(12) << "Angle"
         << setw(15) << "Cosine"
         << setw(15) << "Sine"
         << setw(15) << "Tangent"
         << setw(15) << "Refined T"
         << setw(12) << "Iteration"
         << "\n";
    cout << "=====================================================\n";
}

// ============================================================================
// Main Program
// ============================================================================
int main(int c, char * argv[]) {

    // ========================================================================
    // INITIALIZATION SECTION
    // ========================================================================
    
    // Starting angle value
    double n = 1;
    
    // Exponent for divisor (scales the angle down by 10^exp)
    // Example: exp=4 means divide angle by 10000
    int exp = 4;
    
    // Calculate the primary divisor for angle scaling
    double divisor = pow(10, exp);
    
    // Calculate the decimal increment used for iterative refinement
    // This provides fine-grained steps for convergence
    double decimal = 1 / pow(10, (exp + 5));
    
    // Maximum angle value to test (in units of 1/divisor radians)
    double maxAngle = 100;
    
    // Print formatted output header
    printHeader();
    
    // ========================================================================
    // MAIN ITERATION LOOP
    // ========================================================================
    // Loop through angle values from 1 to maxAngle
    while (n < maxAngle) {
        
        // ====================================================================
        // SINE CALCULATION SECTION
        // ====================================================================
        // Calculate sine of the scaled angle
        double scaledAngle = n / divisor;
        double r = sin(scaledAngle);
        
        // Initialize tracking variables for sine
        // t: intermediate calculation variable
        // m: comparison metric for sine convergence
        double t = (-1) * n * r;
        double m = ((n / t) - (t / n)) - (n / t);
        
        // Format sine value to 12 decimal places for precision
        char y[10];
        sprintf(y, "%.12f", r);
        r = strtod(y, NULL);
        
        // Counter and accumulator for iterative refinement
        double x = 0;
        int iterationCount = 0;
        
        // ====================================================================
        // TANGENT CALCULATION SECTION
        // ====================================================================
        // Calculate tangent of the scaled angle
        double g = pow(n, 2) / divisor;
        double d = tan(scaledAngle);
        double b = ((n / g) - (d / g)) - (n / g);
        
        // Format tangent value to 12 decimal places
        char s[10];
        sprintf(s, "%.12f", b);
        b = strtod(s, NULL);
        
        char f[10];
        sprintf(f, "%.12f", d);
        d = strtod(f, NULL);
        
        // ====================================================================
        // COSINE CALCULATION SECTION
        // ====================================================================
        // Calculate cosine of the scaled angle
        double a = pow(n, 2) / divisor;
        double q = cos(scaledAngle);
        double w = ((n / a) - (a / n));
        
        // Format cosine value to 12 decimal places
        char u[10];
        sprintf(u, "%.12f", q);
        q = strtod(u, NULL);
        
        char p[10];
        sprintf(p, "%.12f", w);
        w = strtod(p, NULL);
        
        // ====================================================================
        // CONVERGENCE REFINEMENT LOOP 1: Ascending Phase
        // ====================================================================
        // This loop refines the estimate in the ascending direction
        // Condition: r < m && b > d && w < q
        // Continue while sine is less than metric AND tangent > d AND cosine < q
        while (r < m && b > d && w < q) {
            // Recalculate metrics with refined values
            m = ((n / t) - (t / n) - (n / t));
            b = ((n / t) - (t / n) - (t / n));
            w = ((n / t) - (t / n));
            
            // Format and update cosine estimate
            sprintf(s, "%.12f", w);
            w = strtod(s, NULL);
            
            // Format and update sine metric
            sprintf(s, "%.12f", m);
            m = strtod(s, NULL);
            
            // Update tangent intermediate variable with incremental step
            sprintf(s, "%.12f", pow(n, 2) / divisor + decimal * x);
            t = strtod(s, NULL);
            
            // Format and update tangent metric
            sprintf(s, "%.12f", b);
            b = strtod(s, NULL);
            
            // Increment refinement counter
            x++;
            iterationCount++;
        }
        
        // Adjust tangent value after ascending refinement
        if (x >= 0)
            t -= decimal;
        else
            t += decimal;
        
        // ====================================================================
        // CONVERGENCE REFINEMENT LOOP 2: Descending Phase
        // ====================================================================
        // This loop refines the estimate in the descending direction
        // Condition: r > m && b < d && w > q
        // Continue while sine > metric AND tangent < d AND cosine > q
        while (r > m && b < d && w > q) {
            // Recalculate metrics with refined values
            m = ((n / t) - (t / n) - (n / t));
            b = ((n / t) - (t / n) - (t / n));
            w = ((n / t) - (t / n));
            
            // Format and update cosine estimate
            sprintf(s, "%.12f", w);
            w = strtod(s, NULL);
            
            // Format and update sine metric
            sprintf(s, "%.12f", m);
            m = strtod(s, NULL);
            
            // Update tangent intermediate variable with decremental step
            sprintf(s, "%.12f", pow(n, 2) / divisor + decimal * x);
            t = strtod(s, NULL);
            
            // Format and update tangent metric
            sprintf(s, "%.12f", b);
            b = strtod(s, NULL);
            
            // Decrement refinement counter
            x--;
            iterationCount++;
        }
        
        // Final adjustment to tangent value after descending refinement
        if (x >= 0)
            t -= decimal;
        else
            t += decimal;
        
        // ====================================================================
        // OUTPUT RESULTS
        // ====================================================================
        // Print trigonometric values for this angle iteration
        cout << fixed << setprecision(12)
             << setw(12) << scaledAngle
             << setw(15) << cos(scaledAngle)
             << setw(15) << sin(scaledAngle)
             << setw(15) << tan(scaledAngle)
             << setw(15) << t
             << setw(12) << iterationCount
             << "\n";
        
        // Move to next angle value
        n++;
    }
    
    // ========================================================================
    // PROGRAM TERMINATION
    // ========================================================================
    cout << "\n========== Analysis Complete ==========\n";
    return 1;
}

// ============================================================================
// ALGORITHM EXPLANATION:
// ============================================================================
// This program implements an iterative refinement technique for trigonometric
// analysis. For each angle value:
// 
// 1. CALCULATION: Compute cosine, sine, and tangent of scaled angles
// 
// 2. METRICS: Establish comparison metrics using ratios of angle (n) and
//    intermediate values (t), which help determine convergence direction
// 
// 3. ASCENDING PHASE: Incrementally increase intermediate value (t) until
//    convergence conditions are no longer met
// 
// 4. DESCENDING PHASE: Incrementally decrease intermediate value (t) until
//    convergence conditions are restored
// 
// 5. OUTPUT: Display the computed trigonometric functions and refined estimate
// 
// The algorithm demonstrates how mathematical relationships between
// trigonometric functions can be exploited for numerical analysis and
// estimation techniques.
// ============================================================================

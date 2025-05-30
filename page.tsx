"use client";
import { useState, useEffect } from 'react';
import { PageTitle } from '@/components/layout/page-title';
import { Card, CardContent, CardDescription, CardFooter, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Progress } from '@/components/ui/progress';
import { DEFAULT_HEART_RATE_ZONES, type HeartRateZone } from '@/lib/constants';
import { Target, Settings, PlayCircle } from 'lucide-react';
import { useToast } from '@/hooks/use-toast';

const calculateMhr = (age: number): number => 220 - age;

export default function ZonesPage() {
  const [age, setAge] = useState<number>(30);
  const [maxHeartRate, setMaxHeartRate] = useState<number>(calculateMhr(30));
  const [customMhr, setCustomMhr] = useState<string>(calculateMhr(30).toString());
  const [heartRateZones, setHeartRateZones] = useState<HeartRateZone[]>([]);
  const { toast } = useToast();

  // Mock workout data
  const [workoutTimeInZones, setWorkoutTimeInZones] = useState<Record<string, number>>({
    "Warm Up": 10, // minutes
    "Fat Burn": 20,
    "Cardio": 25,
    "Peak": 5,
    "Max Effort": 0,
  });
  const totalWorkoutTime = Object.values(workoutTimeInZones).reduce((sum, time) => sum + time, 0);


  useEffect(() => {
    updateZones(maxHeartRate);
  }, [maxHeartRate]);

  const handleAgeChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newAge = parseInt(e.target.value);
    if (!isNaN(newAge) && newAge > 0 && newAge <= 120) {
      setAge(newAge);
      const newMhr = calculateMhr(newAge);
      setMaxHeartRate(newMhr);
      setCustomMhr(newMhr.toString());
    } else if (e.target.value === "") {
      setAge(0); // Allow clearing
    }
  };
  
  const handleCustomMhrChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setCustomMhr(e.target.value);
    const newMhr = parseInt(e.target.value);
    if (!isNaN(newMhr) && newMhr > 50 && newMhr < 250) {
      setMaxHeartRate(newMhr);
    } else if (e.target.value === "") {
       // Allow clearing, maybe reset to age-based if age is set
    }
  };

  const updateZones = (mhr: number) => {
    const updatedZones = DEFAULT_HEART_RATE_ZONES.map(zone => ({
      ...zone,
      minBpm: Math.round((zone.minPercent / 100) * mhr),
      maxBpm: Math.round((zone.maxPercent / 100) * mhr),
    }));
    setHeartRateZones(updatedZones);
  };
  
  const handleApplySettings = () => {
    // This function is now mostly handled by useEffect, but can be used for explicit actions
    updateZones(maxHeartRate);
    toast({ title: "Settings Applied", description: "Heart rate zones have been updated." });
  };

  const handleStartWorkout = () => {
    // In a real app, this would start tracking. Here, we just show a toast.
    toast({ title: "Workout Started!", description: "Time in zones will be tracked (simulated)." });
  };


  return (
    <div className="container mx-auto py-2">
      <PageTitle 
        title="Heart Rate Zones" 
        icon={Target}
        description="Personalize your training zones and track workout intensity."
      />
      <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
        <Card className="shadow-lg">
          <CardHeader>
            <CardTitle className="flex items-center gap-2"><Settings /> Zone Configuration</CardTitle>
            <CardDescription>Set your age or Max Heart Rate (MHR) to personalize zones.</CardDescription>
          </CardHeader>
          <CardContent className="space-y-4">
            <div className="space-y-2">
              <Label htmlFor="age">Your Age</Label>
              <Input id="age" type="number" value={age || ""} onChange={handleAgeChange} placeholder="e.g., 30" />
              <p className="text-sm text-muted-foreground">MHR based on age (220 - age): {age > 0 ? calculateMhr(age) : 'N/A'} BPM</p>
            </div>
            <div className="space-y-2">
              <Label htmlFor="customMhr">Or, Custom Max Heart Rate (MHR)</Label>
              <Input id="customMhr" type="number" value={customMhr} onChange={handleCustomMhrChange} placeholder="e.g., 190" />
            </div>
             <p className="text-sm text-muted-foreground">Current MHR used for zones: <strong>{maxHeartRate} BPM</strong></p>
          </CardContent>
          <CardFooter>
            <Button onClick={handleApplySettings} className="w-full">Apply Settings</Button>
          </CardFooter>
        </Card>

        <Card className="shadow-lg">
          <CardHeader>
            <CardTitle className="flex items-center gap-2"><PlayCircle /> Workout Tracker (Simulated)</CardTitle>
            <CardDescription>Time spent in each heart rate zone during your last workout.</CardDescription>
          </CardHeader>
          <CardContent className="space-y-4">
            {heartRateZones.map(zone => (
              <div key={zone.name} className="space-y-1">
                <div className="flex justify-between items-baseline">
                  <span style={{ color: zone.color }} className="font-medium">{zone.name}</span>
                  <span className="text-sm text-muted-foreground">
                    {zone.minBpm} - {zone.maxBpm} BPM
                  </span>
                </div>
                <Progress 
                    value={totalWorkoutTime > 0 ? (workoutTimeInZones[zone.name] / totalWorkoutTime) * 100 : 0} 
                    className="h-3 [&>div]:bg-[--zone-color]"
                    style={{ '--zone-color': zone.color } as React.CSSProperties}
                />
                <p className="text-xs text-right text-muted-foreground">
                    {workoutTimeInZones[zone.name]} min 
                    ({totalWorkoutTime > 0 ? ((workoutTimeInZones[zone.name] / totalWorkoutTime) * 100).toFixed(0) : 0}%)
                </p>
              </div>
            ))}
            <p className="text-sm font-medium text-right">Total Workout Time: {totalWorkoutTime} minutes</p>
          </CardContent>
           <CardFooter>
            <Button onClick={handleStartWorkout} variant="outline" className="w-full">Start New Workout (Simulated)</Button>
          </CardFooter>
        </Card>
      </div>

      <Card className="mt-6 shadow-lg">
        <CardHeader>
          <CardTitle>Your Personalized Heart Rate Zones</CardTitle>
        </CardHeader>
        <CardContent>
          <div className="space-y-3">
            {heartRateZones.length > 0 ? heartRateZones.map(zone => (
              <div key={zone.name} className="flex items-center p-3 rounded-md border" style={{ borderColor: zone.color }}>
                <div className="w-4 h-10 rounded-l-md mr-3" style={{ backgroundColor: zone.color }}></div>
                <div className="flex-1">
                  <h3 className="font-semibold text-lg" style={{ color: zone.color }}>{zone.name}</h3>
                  <p className="text-sm text-muted-foreground">{zone.minPercent}% - {zone.maxPercent}% of MHR</p>
                </div>
                <div className="text-right">
                  <p className="font-medium text-lg">{zone.minBpm} - {zone.maxBpm}</p>
                  <p className="text-sm text-muted-foreground">BPM</p>
                </div>
              </div>
            )) : (
              <p className="text-muted-foreground">Enter your age or MHR to see personalized zones.</p>
            )}
          </div>
        </CardContent>
      </Card>
    </div>
  );
}

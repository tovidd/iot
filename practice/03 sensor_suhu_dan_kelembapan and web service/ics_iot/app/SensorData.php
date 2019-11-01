<?php

namespace App;

use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\SoftDeletes;

class SensorData extends Model
{
    protected $table= 'sensor_data';
    protected $primaryKey= 'id';
    public $incrementing= true;
    use SoftDeletes;
    protected $fillable= [
        'humidity',
        'temperature', 
        'distance'
    ];
}

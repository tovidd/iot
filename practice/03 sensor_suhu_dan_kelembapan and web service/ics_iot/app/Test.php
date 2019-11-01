<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Test extends Model
{
    protected $table= 'tests';
    protected $primaryKey= 'id';
    public $incrementing= true;
    protected $fillable= [
        'message'
    ];
}

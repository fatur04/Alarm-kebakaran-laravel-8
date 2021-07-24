<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Support\Facades\DB;

class Dht11Model extends Model
{
    use HasFactory;
    protected $table = "dht11";
    protected $primaryKey = "id";
    protected $fillable = [
        'id','suhu','kelembaban'
    ];
}

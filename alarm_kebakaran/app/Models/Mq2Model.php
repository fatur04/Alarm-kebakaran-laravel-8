<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Support\Facades\DB;

class Mq2Model extends Model
{
    use HasFactory;
    protected $table = "mq2";
    protected $primaryKey = "id";
    protected $fillable = [
        'id','gas','flame'
    ];
}

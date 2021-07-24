<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\Dht11Controller;
use App\Http\Controllers\Mq2Controller;
use App\Http\Controllers\AuthController;
use App\Http\Controllers\Auth\LoginController;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/
Route::get('/', [LoginController::class, 'showLoginForm']);

Route::get('/index', [Dht11Controller::class, 'index']);
Route::get('/dashboard', [Dht11Controller::class, 'dashboard']);
Route::get('/tabledht', [Dht11Controller::class, 'tabledht']);
Route::get('/dht11', [Dht11Controller::class, 'insert']);

Route::get('/tablemq2', [Mq2Controller::class, 'tablemq2']);
Route::get('/mq2', [Mq2Controller::class, 'insert']);

Auth::routes();

Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');

@extends('layout.template')
@section('title', 'Dashboard')


@section('content')

<h1> Data Sensor Mq2 dan Sensor Flame </h1>
<table class="table table-striped table-hover table-responsive">
<thead>
    <tr>
      <th>No</th>
      <th>Sensor Mq2</th>
      <th>Sensor Flame</th>
      <th>Kondisi</th>
    </tr>
  </thead>
  <tbody>
  @foreach ($mqs as $key => $data)
    <tr>
        <td>{{ $mqs->firstItem() + $key }}</td>
        <td>{{ $data->gas }} </td>
        <td>{{ $data->flame }}</td>
        <td>
            @if ($data->flame == 0)
                <button class="btn btn-danger">Terdeteksi api</button>
            @else
                <button class="btn btn-success">Tidak terdeteksi api</button>
            @endif
        </td>
    </tr>
  @endforeach
  </tbody>
</table>
<div style="float: leftt;">
    Showing
    {{ $mqs->firstItem() }}
    to
    {{ $mqs->lastItem() }}
    of
    {{ $mqs->total() }}
    entries
</div>
<div style="float: right;">
    {{--  {{ $mqs->links() }}  --}}
    {{ $mqs->onEachSide(0)->links() }}
</div>

@endsection

% title: Personal Organization
% generate_footer

# Personal Organization

<span id="last-updated">Last updated: Dec 21, 2025</span>

There are 2 core parts to my personal organization: a [Bullet Journal](https://www.amazon.com/Bullet-Journal-Method-Present-Design/dp/0525533338/) and a calendar.

## Bullet Journal

I make heavy use of “BuJo”. For a brief overview of what it is, see the [How to Bullet Journal](https://www.youtube.com/watch?v=fm15cmYU0IM) video.

Mine has a few modifications though:

* I use a pocket notebook for “Daily Logs” and a digital version for “Monthly Logs” and “Collections” insead of a regular sized notebook for everything for the following reasons:
    * Harder to carry around a regular sized notebook everywhere. I always have my pocket notebook and pen with me.
    * Writing down URLs. You really need copy paste for these. So I put these in my digital “Monthly Log”.
    * Searching. My “Monthly Logs” tend to have a lot of reference material, so quickly finding things became a real hassle.
    * Expanding previous bullets. I managed to embrace the lack of bullet rearranging, but I often found myself preferring to expand existing tasks or notes with sub-bullets in the digital version to keep information centralized a bit more.
* I use the “Monthly Log” to add URL-based entries (like a link to an article and relevant quotes).
* I don’t use the “Index” collection.
* I don’t use the “Calendar Page” in the “Monthly Log” collection.
    * I use a proper calendar for this instead (see “Calendar” section below).
* I don’t use “event” bullets (`o`).
    * I never quite understood how they’re supposed to be used, so instead I treat past unscheduled events as “notes” (`-`) and use a proper calendar for future scheduled events.
* I don’t use “signifiers”.
* For “task” bullets, I use the original 5, plus 2 of my own:
    * “Task incomplete” (`*`).
    * “Task complete” (`x`).
    * “Task migrated forward to the next month” (`>`).
    * “Task migrated back from the Monthly Log to the Future Log” (`<`).
    * “Task migrated back from the Daily Log to the Monthly Log” (`<`).
    * “Task canceled” (`~`).
    * “Task migrated down to a newer Daily log” (`v`).
    * “Task migrated up to the Monthly Log” (`^`).

I try to capture any task in my pocket notebook “Daily Log” first (no matter how small it is and as soon as possible). Example:

<pre><code>
* replace sofa
</code></pre>

If it's a task large enough that it needs breaking down, I then proceed to migrate it to my digital “Monthly Log” and break it down into multiple sub-tasks as indented bullets and with additional context as nested notes. Example:

<pre><code>
* Replace sofa.
  x Order new sofa online.
    - https://some-website.com/sofa777
  ~ Dump old sofa.
  * Give old sofa to Alice and Bob.
    - Tel: (123) 456-7890
</code></pre>

I also migrate tasks from my pocket notebook in 2 other situations. When I do the digital monthly migration, I go over my pocket notebook tasks and migrate ones that are starting to become old (2+ weeks). When I fill up the pocket notebook and going to start a new one, I migrate all of the tasks.

I also try to capture as a note any meaninful thought (funny, emotional, contextual, etc.), event, article (with sub-notes with my thoughts), information, etc.

When it comes to emotional thoughts, it’s pretty useful to capture them so I can “get it off my chest” without having to vent with someone and avoid doing something stupid or reckless. In a few cases I can also come back later and decide whether I want to add a task or a note with my final/cooler thought(s).

### Pocket Notebook Set-Up

I use [Field Notes](https://fieldnotesbrand.com/) pocket notebooks and [Sakura Pigma Micron 01s](https://www.amazon.com/gp/product/B00K3KRJK6/ref=ppx_yo_dt_b_search_asin_title) pens.

### Digital Set-Up

I use my computer, a text editor (vim) and `.txt` files, and a cloud file storage service to synchronize across computers (GitHub).

The directory and file structure I follow the following example:

<pre><code>
notebooks/
├── 2020
│   ├── 00-future-log.txt
│   ├── 01-january.txt
│   ├── ...
│   └── 12-december.txt
├── 2021
│   ├── 00-future-log.txt
│   ├── 01-january.txt
│   ├── ...
│   └── 12-december.txt
├── books.txt
├── golf.txt
└── recipes.txt
</code></pre>

## Calendar

I use a proper calendar (Google Calendar) since—for me—BuJo fell short on calendaring and reminders, specifically:

* Harder to open up the event’s address in the map app (Google Maps). This is specially needed when driving to avoid typing in the address.
* Harder to visualize time slots.
* Lack of notifications minutes prior to the event.
* Harder to share the event with someone.
* Not practical for rescheduling often, which tends to happen much more nowadays.

I try to capture all significant events in my calendar (appointments, social events and outings, haircuts, flights, birthdays, meetings, etc.).
